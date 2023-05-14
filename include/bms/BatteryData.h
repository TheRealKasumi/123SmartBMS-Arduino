/**
 * @file BatteryData.h
 * @author TheRealKasumi
 * @brief Contains a class that holds data of the battery pack.
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

#include <stdint.h>

class BatteryData
{
public:
	BatteryData();
	~BatteryData();

	uint8_t cellCount;
	float cellVoltageMin;
	float cellVoltageMax;
	float cellVoltageBalance;

	uint8_t packSoc;
	float packVoltage;
	float packCurrent;
	float packChargeCurrent;
	float packDischargeCurrent;
	float packCapacity;
	float packRemainingEnergy;

	float lowestCellVoltage;
	uint8_t lowestCellVoltageNumber;
	float highestCellVoltage;
	uint8_t highestCellVoltageNumber;
	float lowestCellTemperature;
	uint8_t lowestCellTemperatureNumber;
	float highestCellTemperature;
	uint8_t highestCellTemperatureNumber;

	bool communicationError;
	bool allowedToCharge;
	bool allowedToDischarge;
	bool alarmMinVoltage;
	bool alarmMaxVoltage;
	bool alarmMinTemperature;
	bool alarmMaxTemperature;

	unsigned long timeStamp;
};