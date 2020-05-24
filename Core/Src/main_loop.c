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

void Initialize(void)
{
	Hardware_Init();
	LCD_I2C_Init(Transmit_For_LCD, Delay_In_Milis, I2C_For_LCD_Reinit);
	LCD_Set_Shifting_Time(2000);
	DS18B20_Init(Set_Pin_Input, Set_Pin_Output, Delays_us, Write_Pin, Read_Pin, Get_Sys_Time);
}

void Main_Loop(void)
{
	float value = 0, previous= 0;
	uint8_t error=0;
	while (1)
	{
		DS18B20_Service();
		if (Get_Temperature(&value))
		{
			if (previous != value)
				LCD_Print_MultiLines("temp = %d - %d", (int) value, (int) (value * 100) % 100);
			previous = value;
			error = 0;
		}
		else if(!error)
		{
			error = 1;
			LCD_Print_MultiLines("ERROR");
		}
		LCD_Service();
		/*
		 LCD_Print_MultiLines("temp = %d - %d", (int) value, Get_Sys_Seconds());
		 if (value != Get_Sys_Seconds())
		 {
		 value = Get_Sys_Seconds();
		 LCD_Service();
		 float temp = 0;
		 if (Get_Current_Temperature(&temp))
		 {
		 LCD_Print_MultiLines("temp = %d.%d", (int) temp, (int) (temp * 100) % 100);
		 }
		 else
		 {
		 LCD_Print_With_Position("ERROR", 0, 0);
		 }
		 }
		 */
	}
}
