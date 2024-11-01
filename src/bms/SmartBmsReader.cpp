/**
 * @file BMS.cpp
 * @author TheRealKasumi
 * @brief Implementation of the SmartBmsReader class.
 * @copyright Copyright (c) 2024 TheRealKasumi
 * @attention Many thanks to the authors of the https://github.com/123electric/123SmartBMS-Venus project.
 *            The provided code saved my a lot of work decoding the data :) .
 * 			  Check it out!
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "bms/SmartBmsReader.h"

/**
 * @brief Create a new instance of SmartBmsReader.
 * @param inputStream input stream from which the BMS data is read
 */
SmartBmsReader::SmartBmsReader(Stream *inputStream)
{
	// Set the stream and clear it
	this->inputStream_ = inputStream;
	this->inputStream_->flush();
}

/**
 * @brief Destroy the SmartBmsReader instance.
 */
SmartBmsReader::~SmartBmsReader()
{
}

/**
 * @brief Check if the input stream is ready to be read. Once it contains at least 58 bytes, it is considdered ready.
 * @return SmartBmsError::OK when the input stream is ready to be read
 * @return SmartBmsError::NOT_ENOUGH_DATA when not enough data is available yet
 */
const SmartBmsError SmartBmsReader::bmsDataReady() const
{
	return this->inputStream_->available() >= 58 ? SmartBmsError::OK : SmartBmsError::NOT_ENOUGH_DATA;
}

/**
 * @brief Decode a single frame of BMS data from the input stream.
 * @param smartBmsData reference to a SmartBmsData object that will receive the data
 * @return SmartBmsError with error information
 */
const SmartBmsError SmartBmsReader::decodeBmsData(SmartBmsData *smartBmsData) const
{
	// Ensure enough data is available in the input stream
	if (!this->bmsDataReady())
	{
		return SmartBmsError::NOT_ENOUGH_DATA;
	}

	// Create a buffer for the 58 bytes and read it from the input stream
	uint8_t buffer[58] = {0};
	this->inputStream_->readBytes(buffer, sizeof(buffer));

	// Calculate the checksum
	uint8_t checkSum = 0;
	for (size_t i = 0; i < sizeof(buffer) - 1; i++)
	{
		checkSum += buffer[i];
	}

	// Verify the checksum
	if (checkSum != buffer[sizeof(buffer) - 1])
	{
		// Flush the stream
		this->inputStream_->flush();
		return SmartBmsError::INVALID_CHECKSUM;
	}

	// Decode the BMS data from the buffer
	smartBmsData->cellCount_ = buffer[25];
	smartBmsData->cellVoltageMin_ = this->decodeCellVoltage_(&buffer[51]);
	smartBmsData->cellVoltageMax_ = this->decodeCellVoltage_(&buffer[53]);
	smartBmsData->cellVoltageBalance_ = this->decodeCellVoltage_(&buffer[55]);
	smartBmsData->packSoc_ = buffer[40];
	smartBmsData->packVoltage_ = this->decodePackVoltage_(&buffer[0]);
	smartBmsData->packCurrent_ = this->decodePackCurrent_(&buffer[9]);
	smartBmsData->packChargeCurrent_ = this->decodePackCurrent_(&buffer[3]);
	smartBmsData->packDischargeCurrent_ = this->decodePackCurrent_(&buffer[6]);
	smartBmsData->packCapacity_ = this->decodeTwoByteValue_(&buffer[49]) * 0.1f;
	smartBmsData->packRemainingEnergy_ = this->decodeThreeByteValue_(&buffer[34]) * 0.001f;
	smartBmsData->lowestCellVoltage_ = this->decodeCellVoltage_(&buffer[12]);
	smartBmsData->lowestCellVoltageNumber_ = buffer[14];
	smartBmsData->highestCellVoltage_ = this->decodeCellVoltage_(&buffer[15]);
	smartBmsData->highestCellVoltageNumber_ = buffer[17];
	smartBmsData->lowestCellTemperature_ = this->decodeCellTemperature_(&buffer[18]);
	smartBmsData->lowestCellTemperatureNumber_ = buffer[20];
	smartBmsData->highestCellTemperature_ = this->decodeCellTemperature_(&buffer[21]);
	smartBmsData->highestCellTemperatureNumber_ = buffer[23];
	smartBmsData->communicationError_ = buffer[30] & 0b00000100;
	smartBmsData->allowedToCharge_ = buffer[30] & 0b00000001;
	smartBmsData->allowedToDischarge_ = buffer[30] & 0b00000010;
	smartBmsData->minVoltageAlarmActive_ = buffer[30] & 0b00001000;
	smartBmsData->maxVoltageAlarmActive_ = buffer[30] & 0b00010000;
	smartBmsData->minTemperatureAlarmActive_ = buffer[30] & 0b00100000;
	smartBmsData->maxTemperatureAlarmActive_ = buffer[30] & 0b01000000;
	return SmartBmsError::OK;
}

/**
 * @brief Decode the pack voltage value from 3 bytes.
 * @param buffer buffer of 3 bytes
 * @return voltage value in V
 */
const float SmartBmsReader::decodePackVoltage_(const uint8_t buffer[3]) const
{
	// Detmerine the raw value and multiply it with the factor
	const uint32_t rawValue = this->decodeThreeByteValue_(buffer);
	return rawValue * 0.005f;
}

/**
 * @brief Decode a current value from 3 bytes.
 * @param buffer buffer of 3 bytes
 * @return current value in A
 */
const float SmartBmsReader::decodePackCurrent_(const uint8_t buffer[3]) const
{
	// Determine the factor based on the first byte
	float factor = 1.0f;
	if (buffer[0] == 'X')
	{
		factor = 0.0f;
	}
	else if (buffer[0] == '-')
	{
		factor = -1.0f;
	}

	// Detmerine the raw value and multiply it with the factor
	const uint16_t rawValue = this->decodeTwoByteValue_(&buffer[1]);
	return factor * rawValue * 0.125f;
}

/**
 * @brief Decode a cell voltage value from 2 bytes.
 * @param buffer buffer of 2 bytes
 * @return voltage value in V
 */
const float SmartBmsReader::decodeCellVoltage_(const uint8_t buffer[2]) const
{
	// Detmerine the raw value and multiply it with the factor
	const uint16_t rawValue = this->decodeTwoByteValue_(buffer);
	return rawValue * 0.005f;
}

/**
 * @brief Decode a cell temperature value from 2 bytes.
 * @param buffer buffer of 2 bytes
 * @return temperature value in °C
 */
const float SmartBmsReader::decodeCellTemperature_(const uint8_t buffer[2]) const
{
	// Detmerine the raw value and multiply it with the factor
	const uint16_t rawValue = this->decodeTwoByteValue_(buffer);
	return rawValue * 0.857f - 232.0f;
}

/**
 * @brief Decode a 2 byte value.
 * @param buffer buffer of 2 bytes
 * @return decoded 2 byte value
 */
const uint16_t SmartBmsReader::decodeTwoByteValue_(const uint8_t buffer[2]) const
{
	return (static_cast<uint16_t>(buffer[0]) << 8) | buffer[1];
}

/**
 * @brief Decode a 3 byte value.
 * @param buffer buffer of 3 bytes
 * @return decoded 3 byte value
 */
const uint32_t SmartBmsReader::decodeThreeByteValue_(const uint8_t buffer[3]) const
{
	return (static_cast<uint32_t>(buffer[0]) << 16) | (static_cast<uint16_t>(buffer[1]) << 8) | buffer[2];
}
