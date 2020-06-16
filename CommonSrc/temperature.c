/*
 * temperature.c
 *
 *  Created on: May 20, 2020
 *      Author: Jacek
 */
#include "stdint.h"
#include "temperature.h"

#define SUPPLY_VOLTAGE 3.3f
#define ADC_RESOLUTION 4095
#define COUNT_OF_SAMPLES 65535

temperature_struct temperatureService;

uint8_t Get_Current_Temperature(float *temperature)
{
	if (temperatureService.valueReadedCorrectly)
	{
		*temperature = temperatureService.temperature;
		return 1;
	}
	return 0;
}

uint8_t Get_Average_Temperature(float *temperature)
{
	return 0; //todo zrobic usredniania z zapisem dla flash
}

void Temperature_Service(uint32_t adcValue)
{
	static float sumOfTemperatures = 0;
	temperatureService.samplesCounter++;
	sumOfTemperatures += (SUPPLY_VOLTAGE / ADC_RESOLUTION) * adcValue * 100.0;

	if(temperatureService.samplesCounter == COUNT_OF_SAMPLES)
	{
		temperatureService.samplesCounter = 0;
		temperatureService.temperature = sumOfTemperatures/COUNT_OF_SAMPLES;
		temperatureService.valueReadedCorrectly = 1;
		sumOfTemperatures = 0;
	}
}
