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

// Some configuration
#define SERIAL_BAUD_RATE 115200
#define BMS_SERIAL_RX_PIN 3
#define BMS_SERIAL_BAUD_RATE 9600
#define BMS_SERIAL_INVERT false

// Some bad practice global vars
// (Sorry was around 02:00 when I wrote this)
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

	// Create an {@link BMS} instance to decode its data
	bms = new BMS(bmsSerial);

	// Switch an output pin depending on SOC
	// Do what ever you need for your purpose instead
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
}

/**
 * @brief Endless loop.
 */
void loop()
{
	// Read the BMS data
	const int result = bms->readBatteryData(1000);
	if (result == 1)
	{
		Serial.println("Warn: Failed to read BMS data. Timeout occurred because no data was received within the timeout.");
		return;
	}
	else if (result == 2)
	{
		Serial.println("The received BMS data is corrupted. Checksum mismatch.");
		return;
	}

	// Get the battery data and print it to the serial monitor
	const BatteryData battery = bms->getBatteryData();
	Serial.println((String) "Cell-Count: " + battery.cellCount);
	Serial.println((String) "Min-Cell-Voltage: " + battery.cellVoltageMin + "V");
	Serial.println((String) "Max-Cell-Voltage: " + battery.cellVoltageMax + "V");
	Serial.println((String) "Balance-Voltage: " + battery.cellVoltageBalance + "V");
	Serial.println((String) "Pack-SOC: " + battery.packSoc + "%");
	Serial.println((String) "Pack-Voltage: " + battery.packVoltage + "V");
	Serial.println((String) "Pack-Current: " + battery.packCurrent + "A");
	Serial.println((String) "Pack-Charge-Current: " + battery.packChargeCurrent + "A");
	Serial.println((String) "Pack-Discharge-Current: " + battery.packDischargeCurrent + "A");
	Serial.println((String) "Pack-Capacity: " + battery.packCapacity + "kWh");
	Serial.println((String) "Pack-Energy: " + battery.packRemainingEnergy + "kWh");
	Serial.println((String) "Lowest-Cell-Voltage: " + battery.lowestCellVoltage + "V");
	Serial.println((String) "Lowest-Cell-Voltage-Numer: " + battery.lowestCellVoltageNumber);
	Serial.println((String) "Highest-Cell-Voltage: " + battery.highestCellVoltage + "V");
	Serial.println((String) "Highest-Cell-Voltage-Number: " + battery.highestCellVoltageNumber);
	Serial.println((String) "Lowest-Cell-Temp: " + battery.lowestCellTemperature + "°C");
	Serial.println((String) "Lowest-Cell-Temp-Number: " + battery.lowestCellTemperatureNumber);
	Serial.println((String) "Highest-Cell-Temp: " + battery.highestCellTemperature + "°C");
	Serial.println((String) "Highest-Cell-Temp-Number: " + battery.highestCellTemperatureNumber);
	Serial.println((String) "Allowed-Charge: " + (battery.allowedToCharge ? "Yes" : "No"));
	Serial.println((String) "Allowed-Discharge: " + (battery.allowedToDischarge ? "Yes" : "No"));
	Serial.println((String) "Alarm-Communication-Error: " + (battery.communicationError ? "Active" : "Inactive"));
	Serial.println((String) "Alarm-Min-Voltage: " + (battery.alarmMinVoltage ? "Active" : "Inactive"));
	Serial.println((String) "Alarm-Max-Voltage: " + (battery.alarmMaxVoltage ? "Active" : "Inactive"));
	Serial.println((String) "Alarm-Min-Temp: " + (battery.alarmMinTemperature ? "Active" : "Inactive"));
	Serial.println((String) "Alarm-Max-Temp: " + (battery.alarmMaxTemperature ? "Active" : "Inactive"));

	// Switch the signal pin on/off
	// Do what ever you need for your purpose instead
	if (battery.packSoc < 70)
	{
		digitalWrite(13, LOW);
	}
	else if (battery.packSoc > 95)
	{
		digitalWrite(13, HIGH);
	}
}
