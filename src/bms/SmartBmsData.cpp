/**
 * @file SmartBmsData.cpp
 * @author TheRealKasumi
 * @brief Implementation of SmartBmsData.
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
#include "bms/SmartBmsData.h"

/**
 * @brief Create a new instance of SmartBmsData.
 */
SmartBmsData::SmartBmsData()
{
	this->cellCount_ = 0;
	this->cellVoltageMin_ = 0.0f;
	this->cellVoltageMax_ = 0.0f;
	this->cellVoltageBalance_ = 0.0f;
	this->packSoc_ = 0;
	this->packVoltage_ = 0.0f;
	this->packCurrent_ = 0.0f;
	this->packChargeCurrent_ = 0.0f;
	this->packDischargeCurrent_ = 0.0f;
	this->packCapacity_ = 0.0f;
	this->packRemainingEnergy_ = 0.0f;
	this->lowestCellVoltage_ = 0.0f;
	this->lowestCellVoltageNumber_ = 0;
	this->highestCellVoltage_ = 0.0f;
	this->highestCellVoltageNumber_ = 0;
	this->lowestCellTemperature_ = 0.0f;
	this->lowestCellTemperatureNumber_ = 0;
	this->highestCellTemperature_ = 0.0f;
	this->highestCellTemperatureNumber_ = 0;
	this->communicationError_ = 0;
	this->allowedToCharge_ = 0;
	this->allowedToDischarge_ = 0;
	this->minVoltageAlarmActive_ = 0;
	this->maxVoltageAlarmActive_ = 0;
	this->minTemperatureAlarmActive_ = 0;
	this->maxTemperatureAlarmActive_ = 0;
}

/**
 * @brief Destroy the SmartBmsData instance.
 */
SmartBmsData::~SmartBmsData()
{
}

const uint8_t SmartBmsData::getCellCount() const
{
	return this->cellCount_;
}

const float SmartBmsData::getCellVoltageMin() const
{
	return this->cellVoltageMin_;
}

const float SmartBmsData::getCellVoltageMax() const
{
	return this->cellVoltageMax_;
}

const float SmartBmsData::getCellVoltageBalance() const
{
	return this->cellVoltageBalance_;
}

const uint8_t SmartBmsData::getPackSoc() const
{
	return this->packSoc_;
}

const float SmartBmsData::getPackVoltage() const
{
	return this->packVoltage_;
}

const float SmartBmsData::getPackCurrent() const
{
	return this->packCurrent_;
}

const float SmartBmsData::getPackChargeCurrent() const
{
	return this->packChargeCurrent_;
}

const float SmartBmsData::getPackDischargeCurrent() const
{
	return this->packDischargeCurrent_;
}

const float SmartBmsData::getPackCapacity() const
{
	return this->packCapacity_;
}

const float SmartBmsData::getPackRemainingEnergy() const
{
	return this->packRemainingEnergy_;
}

const float SmartBmsData::getLowestCellVoltage() const
{
	return this->lowestCellVoltage_;
}

const uint8_t SmartBmsData::getLowestCellVoltageNumber() const
{
	return this->lowestCellVoltageNumber_;
}

const float SmartBmsData::getHighestCellVoltage() const
{
	return this->highestCellVoltage_;
}

const uint8_t SmartBmsData::getHighestCellVoltageNumber() const
{
	return this->highestCellTemperatureNumber_;
}

const float SmartBmsData::getLowestCellTemperature() const
{
	return this->highestCellTemperature_;
}

const uint8_t SmartBmsData::getLowestCellTemperatureNumber() const
{
	return this->lowestCellTemperatureNumber_;
}

const float SmartBmsData::getHighestCellTemperature() const
{
	return this->highestCellTemperature_;
}

const uint8_t SmartBmsData::getHighestCellTemperatureNumber() const
{
	return this->highestCellTemperatureNumber_;
}

const bool SmartBmsData::hasCommunicationError() const
{
	return this->communicationError_;
}

const bool SmartBmsData::isAllowedToCharge() const
{
	return this->allowedToCharge_;
}

const bool SmartBmsData::isAllowedToDischarge() const
{
	return this->allowedToDischarge_;
}

const bool SmartBmsData::isMinVoltageAlarmActive() const
{
	return this->minVoltageAlarmActive_;
}

const bool SmartBmsData::isMaxVoltageAlarmActive() const
{
	return this->maxVoltageAlarmActive_;
}

const bool SmartBmsData::isMinTemperatureAlarmActive() const
{
	return this->minTemperatureAlarmActive_;
}

const bool SmartBmsData::isMaxTemperatureAlarmActive() const
{
	return this->maxTemperatureAlarmActive_;
}
