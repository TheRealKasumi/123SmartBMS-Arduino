/**
 * @file BMS.cpp
 * @author TheRealKasumi
 * @brief Implementation of the {@link BMS}
 * @copyright Copyright (c) 2023 TheRealKasumi
 * @attention Many thanks to the authors of the https://github.com/123electric/123SmartBMS-Venus project.
 *            The provided code saved my a lot of work decoding the data :) .
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
#include "bms/BMS.h"

/**
 * @brief Create a new instance of {@link BMS}.
 * @param stream input stream from which the BMS data is read
 */
BMS::BMS(Stream *stream)
{
	// Set the stream and clear it
	this->stream = stream;
	this->stream->flush();
}

/**
 * @brief Destroy the {@link BMS} instance.
 */
BMS::~BMS()
{
}

/**
 * @brief Read the {@link BatteryData} from the BMS.
 * @param timeout maximum time in ms to wait for battery data
 * @return 0 when successful
 * @return 1 when timeout
 * @return 2 when checksum error
 */
const int BMS::readBatteryData(const unsigned long timeout)
{
	// Create a buffer for the 58 bytes of BMS data
	uint8_t buffer[58] = {0};
	size_t bufferIndex = 0;

	// Read all 58 bytes from the stream
	// Will be aborted once the timeout is reached
	const unsigned long startTime = millis();
	while (bufferIndex < sizeof(buffer))
	{
		// Read newly available data into the buffer
		if (this->stream->available())
		{
			buffer[bufferIndex++] = this->stream->read();
		}

		// Check for timeouts
		else if (millis() - startTime > timeout)
		{
			return 1;
		}
	}

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
		this->stream->flush();
		return 2;
	}

	// Read the battery data from the buffer and decode it
	this->batteryData.cellCount = buffer[25];
	this->batteryData.cellVoltageMin = this->decodeCellVoltage(&buffer[51]);
	this->batteryData.cellVoltageMax = this->decodeCellVoltage(&buffer[53]);
	this->batteryData.cellVoltageBalance = this->decodeCellVoltage(&buffer[55]);
	this->batteryData.packSoc = buffer[40];
	this->batteryData.packVoltage = this->decodePackVoltage(&buffer[0]);
	this->batteryData.packCurrent = this->decodePackCurrent(&buffer[9]);
	this->batteryData.packChargeCurrent = this->decodePackCurrent(&buffer[3]);
	this->batteryData.packDischargeCurrent = this->decodePackCurrent(&buffer[6]);
	this->batteryData.packCapacity = this->decodeTwoByteValue(&buffer[49]) * 0.1f;
	this->batteryData.packRemainingEnergy = this->decodeThreeByteValue(&buffer[34]) * 0.001f;
	this->batteryData.lowestCellVoltage = this->decodeCellVoltage(&buffer[12]);
	this->batteryData.lowestCellVoltageNumber = buffer[14];
	this->batteryData.highestCellVoltage = this->decodeCellVoltage(&buffer[15]);
	this->batteryData.highestCellVoltageNumber = buffer[17];
	this->batteryData.lowestCellTemperature = this->decodeCellTemperature(&buffer[18]);
	this->batteryData.lowestCellTemperatureNumber = buffer[20];
	this->batteryData.highestCellTemperature = this->decodeCellTemperature(&buffer[21]);
	this->batteryData.highestCellTemperatureNumber = buffer[23];
	this->batteryData.communicationError = buffer[30] & 0b00000100;
	this->batteryData.allowedToCharge = buffer[30] & 0b00000001;
	this->batteryData.allowedToDischarge = buffer[30] & 0b00000010;
	this->batteryData.alarmMinVoltage = buffer[30] & 0b00001000;
	this->batteryData.alarmMaxVoltage = buffer[30] & 0b00010000;
	this->batteryData.alarmMinTemperature = buffer[30] & 0b00100000;
	this->batteryData.alarmMaxTemperature = buffer[30] & 0b01000000;
	this->batteryData.timeStamp = millis();

	return 0;
}

/**
 * @brief Get the {@link BatteryData}.
 * @return reference to the battery data
 */
const BatteryData &BMS::getBatteryData()
{
	return this->batteryData;
}

/**
 * @brief Decode the pack voltage value from 3 bytes.
 * @param buffer buffer of 3 bytes
 * @return voltage value in V
 */
const float BMS::decodePackVoltage(const uint8_t buffer[3])
{
	// Detmerine the raw value and multiply it with the factor
	const uint32_t rawValue = this->decodeThreeByteValue(buffer);
	return rawValue * 0.005f;
}

/**
 * @brief Decode a current value from 3 bytes.
 * @param buffer buffer of 3 bytes
 * @return current value in A
 */
const float BMS::decodePackCurrent(const uint8_t buffer[3])
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
	const uint16_t rawValue = this->decodeTwoByteValue(&buffer[1]);
	return factor * rawValue * 0.125f;
}

/**
 * @brief Decode a cell voltage value from 2 bytes.
 * @param buffer buffer of 2 bytes
 * @return voltage value in V
 */
const float BMS::decodeCellVoltage(const uint8_t buffer[2])
{
	// Detmerine the raw value and multiply it with the factor
	const uint16_t rawValue = this->decodeTwoByteValue(buffer);
	return rawValue * 0.005f;
}

/**
 * @brief Decode a cell temperature value from 2 bytes.
 * @param buffer buffer of 2 bytes
 * @return temperature value in °C
 */
const float BMS::decodeCellTemperature(const uint8_t buffer[2])
{
	// Detmerine the raw value and multiply it with the factor
	const uint16_t rawValue = this->decodeTwoByteValue(buffer);
	return rawValue * 0.857f - 232.0f;
}

/**
 * @brief Decode a 2 byte value.
 * @param buffer buffer of 2 bytes
 * @return decoded 2 byte value
 */
const uint16_t BMS::decodeTwoByteValue(const uint8_t buffer[2])
{
	return (static_cast<uint16_t>(buffer[0]) << 8) | buffer[1];
}

/**
 * @brief Decode a 3 byte value.
 * @param buffer buffer of 3 bytes
 * @return decoded 3 byte value
 */
const uint32_t BMS::decodeThreeByteValue(const uint8_t buffer[3])
{
	return (static_cast<uint32_t>(buffer[0]) << 16) | (static_cast<uint16_t>(buffer[1]) << 8) | buffer[2];
}
