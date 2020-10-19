/*
 * temperatureService.cpp
 *
 *  Created on: 18 paź 2020
 *      Author: Jacek
 */

#include "temperatureService.h"
#include "globalDefines.h"
#include "adcService.h"
#include <vector>
#include "list"

TemperatureService::TemperatureService(ADCAveragingService *adcService)
{
	if (adcService == 0)
	{
		throw "Set valid object pointer!";
	}
	else
	{
		this->adcService = adcService;
	}
}

TemperatureService::~TemperatureService()
{
	for (auto it = tempConversions.begin(); it != tempConversions.end(); ++it)
	{
		delete (*it).calculationMethod;
	}
	tempConversions.clear();
	temperatures.clear();
}

void TemperatureService::Add_Temperature_Calculation_Object(TemperatureCalculation *calculationMethod, ADCChannelNumbers channelNumber)
{
	tempConversions.push_back(
	{ calculationMethod, channelNumber });
}

void TemperatureService::Update_Temperatures()
{
	float temperature;
	float percentageOfVoltage;
	uint8_t index = 0;
	if (temperatures.size() != tempConversions.size())
	{
		temperatures.resize(tempConversions.size(), 0);
	}
	for (auto it = tempConversions.begin(); it != tempConversions.end(); ++it)
	{
		auto putPosition = temperatures.begin();
		advance(putPosition, index++);
		percentageOfVoltage = adcService->Get_Percentage_Of_Supply_Voltage_For_Channel(it->adcChannel);
		temperature = (*it).calculationMethod->Get_Temperature_For_Percentage_Of_Voltage(percentageOfVoltage);
		temperatures.insert(putPosition, temperature);
	}
}

float TemperatureService::Get_Temperature(SensorNumber sensorNumber)
{
	if (sensorNumber >= temperatures.size())
	{
		return 0;
	}
	else
	{
		auto iterator = temperatures.begin();
		advance(iterator, sensorNumber);
		return *iterator;
	}
}
