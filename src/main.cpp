/**
 * @file main.cpp
 * @author TheRealKasumi
 * @brief Entry point.
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
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "bms/BMS.h"

// Configuration
#define SERIAL_BAUD_RATE 115200
#define BMS_SERIAL_RX_PIN 3
#define BMS_SERIAL_BAUD_RATE 9600
#define BMS_SERIAL_INVERT false

// Global instances
SoftwareSerial *bmsSerial = nullptr;
BMS *bms = nullptr;

/**
 * @brief Setup.
 */
void setup()
{
	// Initialize the (PC) serial
	Serial.begin(SERIAL_BAUD_RATE);

	// Initialize the (BMS) serial
	bmsSerial = new SoftwareSerial(BMS_SERIAL_RX_PIN, -1, BMS_SERIAL_INVERT);
	bmsSerial->begin(BMS_SERIAL_BAUD_RATE);

	// Create an {@link BMS} instance
	bms = new BMS(bmsSerial);
}

/**
 * @brief Endless loop.
 */
void loop()
{
	// Read the BMS data
	const int result = bms->readBatteryData(500);
	if (result == 1)
	{
		Serial.println("Warn: Failed to read BMS data. Timeout occured because no data was received within the timeout.");
	}
	else if (result == 2)
	{
		Serial.println("Error: The received BMS data is corrupte. Checksum mismatch.");
	}

	// Get the battery data and print it
	const BatteryData bat = bms->getBatteryData();
	Serial.println((String) "Cell-Count: " + bat.cellCount);
	Serial.println((String) "Min-Cell-Voltage: " + bat.cellVoltageMin + "V");
	Serial.println((String) "Max-Cell-Voltage: " + bat.cellVoltageMax + "V");
	Serial.println((String) "Balance-Voltage: " + bat.cellVoltageBalance + "V");
	Serial.println((String) "Pack-SOC: " + bat.packSoc + "%");
	Serial.println((String) "Pack-Voltage: " + bat.packVoltage + "V");
	Serial.println((String) "Pack-Current: " + bat.packCurrent + "A");
	Serial.println((String) "Pack-Charge-Current: " + bat.packChargeCurrent + "A");
	Serial.println((String) "Pack-Discharge-Current: " + bat.packDischargeCurrent + "A");
	Serial.println((String) "Pack-Capacity: " + bat.packCapacity + "kWh");
	Serial.println((String) "Pack-Energy: " + bat.packRemainingEnergy + "kWh");
	Serial.println((String) "Lowest-Cell-Voltage: " + bat.lowestCellVoltage + "V");
	Serial.println((String) "Lowest-Cell-Voltage-Numer: " + bat.lowestCellVoltageNumber);
	Serial.println((String) "Highest-Cell-Voltage: " + bat.highestCellVoltage + "V");
	Serial.println((String) "Highest-Cell-Voltage-Number: " + bat.highestCellVoltageNumber);
	Serial.println((String) "Lowest-Cell-Temp: " + bat.lowestCellTemperature + "°C");
	Serial.println((String) "Lowest-Cell-Temp-Number: " + bat.lowestCellTemperatureNumber);
	Serial.println((String) "Highest-Cell-Temp: " + bat.highestCellTemperature + "°C");
	Serial.println((String) "Highest-Cell-Temp-Number: " + bat.highestCellTemperatureNumber);
	Serial.println((String) "Allowed-Charge: " + (bat.allowedToCharge ? "Yes" : "No"));
	Serial.println((String) "Allowed-Discharge: " + (bat.allowedToDischarge ? "Yes" : "No"));
	Serial.println((String) "Alarm-Communication-Error: " + (bat.communicationError ? "Active" : "Inactive"));
	Serial.println((String) "Alarm-Min-Voltage: " + (bat.alarmMinVoltage ? "Active" : "Inactive"));
	Serial.println((String) "Alarm-Max-Voltage: " + (bat.alarmMaxVoltage ? "Active" : "Inactive"));
	Serial.println((String) "Alarm-Min-Temp: " + (bat.alarmMinTemperature ? "Active" : "Inactive"));
	Serial.println((String) "Alarm-Max-Temp: " + (bat.alarmMaxTemperature ? "Active" : "Inactive"));
}
