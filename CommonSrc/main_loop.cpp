/*
 * main_loop.c
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */
#include <adcService.h>
#include <internalSensorTemperature.h>
#include "timer.h"
#include "HAL_Functions.h"
#include "LCD_I2C.h"
#include "DS18B20_One_Wire.h"
#include "main.h"
#include "main_loop.h"
#include "globalObjects.h"
#include "PinsService.h"
#include "LM35Sensor.h"

volatile float temperature = 0;

void Initialize(void)
{
	Hardware_Init();
	LCD_I2C_Init(Transmit_For_LCD, Delay_In_Milis, I2C_Reinit_For_LCD);
	LCD_Set_Shifting_Time(2000);
	DS18B20_Init(Set_Pin_Input, Set_Pin_Output, Delays_us, Write_Pin, Read_Pin, Get_Sys_Time);
	LCD_Clear();
}

void Main_Loop(void)
{
	adcService.Update_Average_ADC_Values();
	DS18B20_Service();
	LCD_Service();
	LM35Temp.Get_Temperature_For_Percentage_Of_Voltage(adcService.Get_Percentage_Of_Supply_Voltage_For_Channel(0));
	temperature = internalTemp.Get_Temperature_For_Percentage_Of_Voltage(adcService.Get_Percentage_Of_Supply_Voltage_For_Channel(1));

}
