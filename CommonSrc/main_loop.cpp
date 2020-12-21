/*
 * main_loop.c
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */
#include <adcService.h>
#include <ds18b20OneWire.h>
#include <halFunctions.h>
#include <internalSensorTemperature.h>
#include <lcd_i2c.h>
#include <lm35Sensor.h>
#include <pinsService.h>
#include "timer.h"
#include "main.h"
#include "main_loop.h"
#include "globalObjects.h"
#include "temperatureService.h"
#include "cstdio"
#include "dht11.h"

using namespace std;

void Functions_Called_Once_Every_Second()
{
	static uint32_t previousSecond = 0;

	if (previousSecond != Get_Sys_Seconds())
	{
		previousSecond = Get_Sys_Seconds();
		temperatureService.Update_Temperatures();
		photresistor.Calculate_Resistance_For_Voltage_Percentage(adcService.Get_Percentage_Of_Supply_Voltage_For_Channel(PHOTRESISTOR_SENSOR_INPUT));
	}
}

void Main_Loop(void)
{
	adcService.Update_Average_ADC_Values();
	DS18B20_Service();
	LCD_Service();
	pinsFiltering.Filter_Pins_States();
	Functions_Called_Once_Every_Second();
	dht11.Communication_Loop();
}
