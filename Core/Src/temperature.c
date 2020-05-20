/*
 * temperature.c
 *
 *  Created on: May 20, 2020
 *      Author: Jacek
 */
#include "stdint.h"

#define SUPPLY_VOLTAGE 3.3f
#define ADC_RESOLUTION 4095
float currentTemperature;
uint8_t status = 0;

uint8_t Get_Current_Temperature(float *temperature)
{
	if (status)
	{
		*temperature = currentTemperature;
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
	static uint32_t count = 0;
	if (Get_Sys_Seconds() % 2 == 0)
	{
		count = 0;
		status = 0;
	}
	else
	{
		count++;
	}
	status = 1;
	currentTemperature = (SUPPLY_VOLTAGE / ADC_RESOLUTION) * adcValue * 100.0;
}
