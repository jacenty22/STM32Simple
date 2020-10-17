/*
 * LM35Sensor.cpp
 *
 *  Created on: 17 paź 2020
 *      Author: Jacek
 */
#include "LM35Sensor.h"

LM35TemperatureCalculation::LM35TemperatureCalculation(float supplyVoltage, float averageSlope) :
		TemperatureCalculation(supplyVoltage,averageSlope)
{

}

LM35TemperatureCalculation::~LM35TemperatureCalculation()
{
}

float LM35TemperatureCalculation::Get_Temperature_For_Percentage_Of_Voltage(float percentage)
{
	float voltage = percentage / 100.0f * supplyVoltage;
	voltage *= 1000;//milivolty
	float temperature = voltage / averageSlope;
	return temperature;
}

