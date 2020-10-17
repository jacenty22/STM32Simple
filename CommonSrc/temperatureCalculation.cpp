/*
 * temperatureCalculation.cpp
 *
 *  Created on: 15 paź 2020
 *      Author: Jacek
 */
#include "temperatureCalculation.h"

TemperatureCalculation::TemperatureCalculation(float supplyVoltage, float averageSlope)
{
	Set_Supply_Voltage(supplyVoltage);
	Set_Average_Slope(averageSlope);
}

TemperatureCalculation::~TemperatureCalculation()
{

}

void TemperatureCalculation::Set_Supply_Voltage(float suuplyVoltage)
{
	this->supplyVoltage = suuplyVoltage;
}

void TemperatureCalculation::Set_Average_Slope(float averageSlope)
{
	this->averageSlope = averageSlope;
}

float TemperatureCalculation::Get_Supply_Voltage()
{
	return supplyVoltage;
}

float TemperatureCalculation::Get_Average_Slope()
{
	return averageSlope;
}
