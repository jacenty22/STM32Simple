/*
 * main_loop.c
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */
#include "timer.h"
#include "temperature.h"
#include "HAL_Functions.h"
#include "LCD_I2C.h"
#include "DS18B20_One_Wire.h"
#include "main.h"
uint32_t time = 0;
uint16_t volatile adcValue = 0;
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
	if(Get_Sys_Seconds() != time)
	{
		if(tablicaADC[0])
			time = Get_Sys_Seconds();

		LCD_Print_In_Separately_Line("kupa",0);
		LCD_Print_In_Separately_Line("kupa",1);
	}
	DS18B20_Service();
	LCD_Service();
}
