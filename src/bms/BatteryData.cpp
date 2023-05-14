/**
 * @file BatteryData.cpp
 * @author TheRealKasumi
 * @brief Implementation of {@link BatteryData}.
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
#include "bms/BatteryData.h"

/**
 * @brief Create a new instance of {@link BatteryData}.
 */
BatteryData::BatteryData()
{
	this->cellCount = 0;
	this->cellVoltageMin = 0.0f;
	this->cellVoltageMax = 0.0f;
	this->cellVoltageBalance = 0.0f;
	this->packSoc = 0;
	this->packVoltage = 0.0f;
	this->packCurrent = 0.0f;
	this->packChargeCurrent = 0.0f;
	this->packDischargeCurrent = 0.0f;
	this->packCapacity = 0.0f;
	this->packRemainingEnergy = 0.0f;
	this->lowestCellVoltage = 0.0f;
	this->lowestCellVoltageNumber = 0;
	this->highestCellVoltage = 0.0f;
	this->highestCellVoltageNumber = 0;
	this->lowestCellTemperature = 0.0f;
	this->lowestCellTemperatureNumber = 0;
	this->highestCellTemperature = 0.0f;
	this->highestCellTemperatureNumber = 0;
	this->communicationError = 0;
	this->allowedToCharge = 0;
	this->allowedToDischarge = 0;
	this->alarmMinVoltage = 0;
	this->alarmMaxVoltage = 0;
	this->alarmMinTemperature = 0;
	this->alarmMaxTemperature = 0;
	this->timeStamp = 0;
}

/**
 * @brief Destroy the {@link BatteryData} instance.
 */
BatteryData::~BatteryData()
{
}
