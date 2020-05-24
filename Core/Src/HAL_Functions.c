/*
 * Hal_Functions.c
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */

#include "HAL_Functions.h"
#include "main.h"

void Hardware_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_ADC_Start_IT(&hadc1);
}
uint8_t Transmit_For_LCD(uint16_t deviceAddress, uint8_t *data, size_t dataSize, uint32_t timeout)
{
	return HAL_I2C_Master_Transmit(&hi2c1, deviceAddress, (uint8_t*) data, dataSize, timeout);
}
void Delay_In_Milis(uint32_t delay)
{
	HAL_Delay(delay);
}

void I2C_For_LCD_Reinit(void)
{
	HAL_I2C_DeInit(&hi2c1);
	HAL_Delay(100);
	HAL_I2C_Init(&hi2c1);
}

void Delays_us(const uint16_t us_time)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while (__HAL_TIM_GET_COUNTER(&htim1) < us_time)
		;
}
