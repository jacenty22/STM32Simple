/*
 * temperature.c
 *
 *  Created on: May 20, 2020
 *      Author: Jacek
 */
#include <internalSensorTemperature.h>
#include "stdint.h"
#include "temperatureCalculation.h"

InternalSensorTempCalc::InternalSensorTempCalc(float supplyVoltage, float voltageForNDegrees, float NDegrees, float averageSlope) :
		TemperatureCalculation(supplyVoltage, averageSlope)
{
	this->voltageForNDegrees = voltageForNDegrees;
	this->NDegrees = NDegrees;
}

InternalSensorTempCalc::~InternalSensorTempCalc()
{
}

float InternalSensorTempCalc::Get_Temperature_For_Percentage_Of_Voltage(float percentage)
{
	float temperature;
	float voltage = voltageForNDegrees - supplyVoltage * percentage / 100.0f;
	voltage *= 1000;	//zamiana na milivolty
	temperature = voltage / averageSlope;
	temperature += NDegrees;
	return temperature;
}
