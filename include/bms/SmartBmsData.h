/**
 * @file SmartBmsData.h
 * @author TheRealKasumi
 * @brief Contains a class that holds data of the battery pack.
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
#ifndef SMART_BMS_DATA_H
#define SMART_BMS_DATA_H

#include <stdint.h>

#include "bms/SmartBmsReader.h"

class SmartBmsReader;

class SmartBmsData
{
public:
	SmartBmsData();
	~SmartBmsData();

	const uint8_t getCellCount() const;
	const float getCellVoltageMin() const;
	const float getCellVoltageMax() const;
	const float getCellVoltageBalance() const;

	const uint8_t getPackSoc() const;
	const float getPackVoltage() const;
	const float getPackCurrent() const;
	const float getPackChargeCurrent() const;
	const float getPackDischargeCurrent() const;
	const float getPackCapacity() const;
	const float getPackRemainingEnergy() const;

	const float getLowestCellVoltage() const;
	const uint8_t getLowestCellVoltageNumber() const;
	const float getHighestCellVoltage() const;
	const uint8_t getHighestCellVoltageNumber() const;
	const float getLowestCellTemperature() const;
	const uint8_t getLowestCellTemperatureNumber() const;
	const float getHighestCellTemperature() const;
	const uint8_t getHighestCellTemperatureNumber() const;

	const bool hasCommunicationError() const;
	const bool isAllowedToCharge() const;
	const bool isAllowedToDischarge() const;
	const bool isMinVoltageAlarmActive() const;
	const bool isMaxVoltageAlarmActive() const;
	const bool isMinTemperatureAlarmActive() const;
	const bool isMaxTemperatureAlarmActive() const;

private:
	uint8_t cellCount_;
	float cellVoltageMin_;
	float cellVoltageMax_;
	float cellVoltageBalance_;

	uint8_t packSoc_;
	float packVoltage_;
	float packCurrent_;
	float packChargeCurrent_;
	float packDischargeCurrent_;
	float packCapacity_;
	float packRemainingEnergy_;

	float lowestCellVoltage_;
	uint8_t lowestCellVoltageNumber_;
	float highestCellVoltage_;
	uint8_t highestCellVoltageNumber_;
	float lowestCellTemperature_;
	uint8_t lowestCellTemperatureNumber_;
	float highestCellTemperature_;
	uint8_t highestCellTemperatureNumber_;

	bool communicationError_;
	bool allowedToCharge_;
	bool allowedToDischarge_;
	bool minVoltageAlarmActive_;
	bool maxVoltageAlarmActive_;
	bool minTemperatureAlarmActive_;
	bool maxTemperatureAlarmActive_;

	friend class SmartBmsReader;
};

#endif
