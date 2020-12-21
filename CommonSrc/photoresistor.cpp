/*
 * photoresistor.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Jacek
 */
#include "photoresistor.h"


PhotoresistorResistance::PhotoresistorResistance(float supplyVoltage, float adcMaxVoltage,uint16_t dividerResistance,uint16_t darkThreshold)
{
	this->supplyVoltage = supplyVoltage;
	this->dividerResistance = dividerResistance;
	this->darkThreshold = darkThreshold;
	this->adcMaxVoltage = adcMaxVoltage;
}
bool PhotoresistorResistance::Is_Brightness_Below_Threshold()
{
	return (cellResistance > darkThreshold);
}

//rezystancja wedlug wzoru R=Rd*(U/Ud - 1)
void PhotoresistorResistance::Calculate_Resistance_For_Voltage_Percentage(float dividerPercentageOfVoltage)
{
	dividerPercentageOfVoltage /= 100.0f;
	float dividerVoltage = dividerPercentageOfVoltage * adcMaxVoltage;
	cellResistance = 0;
	if(dividerVoltage > 0)
	{
		cellResistance = supplyVoltage / dividerVoltage;
		cellResistance -= 1;
		cellResistance *= dividerResistance;
	}
}


