/**
 * @file SmartBmsReader.h
 * @author TheRealKasumi
 * @brief Contains a class for reading battery data from the 123SmartBMS.
 * @copyright Copyright (c) 2024 TheRealKasumi
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
#ifndef SMART_BMS_READER_H
#define SMART_BMS_READER_H

#include <stdint.h>
#include <Stream.h>

#include "bms/SmartBmsData.h"
#include "bms/SmartBmsError.h"

class SmartBmsData;

class SmartBmsReader
{
public:
	SmartBmsReader(Stream *inputStream);
	~SmartBmsReader();

	const SmartBmsError bmsDataReady() const;
	const SmartBmsError decodeBmsData(SmartBmsData *smartBmsData) const;

private:
	Stream *inputStream_;

	const float decodePackVoltage_(const uint8_t buffer[3]) const;
	const float decodePackCurrent_(const uint8_t buffer[3]) const;
	const float decodeCellVoltage_(const uint8_t buffer[2]) const;
	const float decodeCellTemperature_(const uint8_t buffer[2]) const;
	const uint16_t decodeTwoByteValue_(const uint8_t buffer[2]) const;
	const uint32_t decodeThreeByteValue_(const uint8_t buffer[3]) const;
};

#endif
