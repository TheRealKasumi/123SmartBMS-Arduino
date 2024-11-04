/**
 * @file main.cpp
 * @author TheRealKasumi
 * @brief Example application
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
#include <HardwareSerial.h>

#include "bms/SmartBmsData.h"
#include "bms/SmartBmsError.h"
#include "bms/SmartBmsReader.h"

// Serial configuration, adjust as needed
#define PC_SERIAL_BAUD 115200
#define BMS_SERIAL_MODE SERIAL_8N1
#define BMS_SERIAL_PERIPHERAL 1
#define BMS_SERIAL_BAUD_RATE 9600
#define BMS_SERIAL_RX_PIN 26
#define BMS_SERIAL_INVERT false

// Serial connections
HardwareSerial smartBmsSerial(BMS_SERIAL_PERIPHERAL);
SmartBmsReader smartBmsReader(&smartBmsSerial);

/**
 * @brief Setup.
 */
void setup()
{
	// Initialize the serial connections
	Serial.begin(PC_SERIAL_BAUD);
	smartBmsSerial.begin(BMS_SERIAL_BAUD_RATE, BMS_SERIAL_MODE, BMS_SERIAL_RX_PIN, -1, BMS_SERIAL_INVERT);
}

/**
 * @brief Endless loop.
 */
void loop()
{
	// Check if enough data was received
	if (smartBmsReader.bmsDataReady() == SmartBmsError::SBMS_OK)
	{
		// Read the BMS data and check for errors
		SmartBmsData smartBmsData;
		const SmartBmsError err = smartBmsReader.decodeBmsData(&smartBmsData);
		if (err == SmartBmsError::SBMS_OK)
		{
			// Data is ok, lets print it
			Serial.println();
			Serial.println("===========================");
			Serial.println((String) "Cell-Count: " + smartBmsData.getCellCount());
			Serial.println((String) "Min-Cell-Voltage: " + smartBmsData.getCellVoltageMin() + "V");
			Serial.println((String) "Max-Cell-Voltage: " + smartBmsData.getCellVoltageMax() + "V");
			Serial.println((String) "Balance-Voltage: " + smartBmsData.getCellVoltageBalance() + "V");
			Serial.println((String) "Pack-SOC: " + smartBmsData.getPackSoc() + "%");
			Serial.println((String) "Pack-Voltage: " + smartBmsData.getPackVoltage() + "V");
			Serial.println((String) "Pack-Current: " + smartBmsData.getPackCurrent() + "A");
			Serial.println((String) "Pack-Charge-Current: " + smartBmsData.getPackChargeCurrent() + "A");
			Serial.println((String) "Pack-Discharge-Current: " + smartBmsData.getPackDischargeCurrent() + "A");
			Serial.println((String) "Pack-Capacity: " + smartBmsData.getPackCapacity() + "kWh");
			Serial.println((String) "Pack-Energy: " + smartBmsData.getPackRemainingEnergy() + "kWh");
			Serial.println((String) "Lowest-Cell-Voltage: " + smartBmsData.getLowestCellVoltage() + "V");
			Serial.println((String) "Lowest-Cell-Voltage-Numer: " + smartBmsData.getLowestCellVoltageNumber());
			Serial.println((String) "Highest-Cell-Voltage: " + smartBmsData.getHighestCellVoltage() + "V");
			Serial.println((String) "Highest-Cell-Voltage-Number: " + smartBmsData.getHighestCellVoltageNumber());
			Serial.println((String) "Lowest-Cell-Temp: " + smartBmsData.getLowestCellTemperature() + "°C");
			Serial.println((String) "Lowest-Cell-Temp-Number: " + smartBmsData.getLowestCellTemperatureNumber());
			Serial.println((String) "Highest-Cell-Temp: " + smartBmsData.getHighestCellTemperature() + "°C");
			Serial.println((String) "Highest-Cell-Temp-Number: " + smartBmsData.getHighestCellTemperatureNumber());
			Serial.println((String) "Allowed-Charge: " + (smartBmsData.isAllowedToCharge() ? "Yes" : "No"));
			Serial.println((String) "Allowed-Discharge: " + (smartBmsData.isAllowedToCharge() ? "Yes" : "No"));
			Serial.println((String) "Alarm-Communication-Error: " + (smartBmsData.hasCommunicationError() ? "Active" : "Inactive"));
			Serial.println((String) "Alarm-Min-Voltage: " + (smartBmsData.isMinVoltageAlarmActive() ? "Active" : "Inactive"));
			Serial.println((String) "Alarm-Max-Voltage: " + (smartBmsData.isMaxVoltageAlarmActive() ? "Active" : "Inactive"));
			Serial.println((String) "Alarm-Min-Temp: " + (smartBmsData.isMinTemperatureAlarmActive() ? "Active" : "Inactive"));
			Serial.println((String) "Alarm-Max-Temp: " + (smartBmsData.isMaxTemperatureAlarmActive() ? "Active" : "Inactive"));
			Serial.println("===========================");
			Serial.println();
		}
		else if (err == SmartBmsError::SBMS_ERR_READ_STREAM)
		{
			// Failed to read the input stream
			Serial.println("Error: Failed to read BMS data. The input stream could not be read.");
			return;
		}
		else if (err == SmartBmsError::SBMS_ERR_INVALID_CHECKSUM)
		{
			// Checksum is invalid, something went very wrong
			Serial.println("Error: Failed to read BMS data. The checksum is invalid.");
			return;
		}
	}

	/*
	 * Do something else in the meantime, but make sure your serial buffer will not overflow.
	 */
}
