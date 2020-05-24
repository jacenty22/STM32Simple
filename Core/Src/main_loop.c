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

static void Initialize(void);
static void Main_Loop(void);

void Main_Function(void)
{
	Initialize();
	Main_Loop();
}

static void Initialize(void)
{
	Hardware_Init();

	LCD_I2C_Init(Transmit_For_LCD, Delay_In_Milis, I2C_For_LCD_Reinit);
	LCD_Set_Shifting_Time(2000);
}

static void Main_Loop(void)
{
	float value = 0;
	while (1)
	{
		value++;
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
	}
}
