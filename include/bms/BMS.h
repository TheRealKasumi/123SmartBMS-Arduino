/**
 * @file BMS.h
 * @author TheRealKasumi
 * @brief Contains a class for reading 123SmartBMS data.
 * @copyright Copyright (c) 2023 TheRealKasumi
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
#include <Arduino.h>
#include "bms/BatteryData.h"

class BMS
{
public:
	BMS(Stream *stream);
	~BMS();

	const int readBatteryData(const unsigned long timeout = 1000);
	const BatteryData &getBatteryData();

private:
	Stream *stream;
	BatteryData batteryData;

	const float decodePackVoltage(const uint8_t buffer[3]);
	const float decodePackCurrent(const uint8_t buffer[3]);
	const float decodeCellVoltage(const uint8_t buffer[2]);
	const float decodeCellTemperature(const uint8_t buffer[2]);
	const uint16_t decodeTwoByteValue(const uint8_t buffer[2]);
	const uint32_t decodeThreeByteValue(const uint8_t buffer[3]);
};
