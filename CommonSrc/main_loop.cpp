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

volatile float temperature = 0;

void Initialize(void)
{
	Hardware_Init();
	Initialize_Global_Objects();
	LCD_I2C_Init(Transmit_For_LCD, Delay_In_Milis, I2C_Reinit_For_LCD);
	LCD_Set_Shifting_Time(2000);
	DS18B20_Init(Set_Pin_Input, Set_Pin_Output, Delays_us, Write_Pin, Read_Pin, Get_Sys_Time);
	LCD_Clear();
}

void Functions_Called_Once_Every_Second()
{
	static uint32_t previousSecond = 0;

	if (previousSecond != Get_Sys_Seconds())
	{
		previousSecond = Get_Sys_Seconds();
		temperatureService.Update_Temperatures();
	}
}

void Main_Loop(void)
{
	adcService.Update_Average_ADC_Values();
	DS18B20_Service();
	LCD_Service();
	Functions_Called_Once_Every_Second();
}
