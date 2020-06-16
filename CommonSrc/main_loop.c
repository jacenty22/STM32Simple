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

}
