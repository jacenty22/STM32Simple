/*
 * Hal_Functions.c
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */

#include <adcService.h>
#include "HAL_Functions.h"
#include "main.h"
#include "timer.h"
#include "globalObjects.h"

TIM_HandleTypeDef *microsecondTimerPtr;
I2C_HandleTypeDef *i2cForLCDPtr;

#if defined(STM32F411xE)

#define I2C_FOR_LCD (hi2c1)
#define MICROSECOND_TIMER (htim1)

#elif defined(STM32F103xB)

#define I2C_FOR_LCD (hi2c1)
#define MICROSECOND_TIMER (htim2)
#define MILISECOND_CALLBACK_TIMER TIM3

#endif

void Hardware_Init(void)
{
	microsecondTimerPtr = &MICROSECOND_TIMER;
	i2cForLCDPtr = &I2C_FOR_LCD;

#if defined(STM32F411xE)
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_ADC_Start_IT(&hadc1);
#elif defined(STM32F103xB)
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_ADC_Start_DMA(&hadc1, adcService.Get_ADC_Array_Address(), adcService.Get_ADC_Array_Size());
#endif
	HAL_GPIO_WritePin(TRANSISTOR_BASE_GPIO_Port, TRANSISTOR_BASE_Pin, GPIO_PIN_SET);
}

void Timers_Callback_Service(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == MILISECOND_CALLBACK_TIMER)
	{
		Time_Service();
	}
}

uint8_t Transmit_For_LCD(uint16_t deviceAddress, uint8_t *data, size_t dataSize, uint32_t timeout)
{
	return HAL_I2C_Master_Transmit(i2cForLCDPtr, deviceAddress, (uint8_t*) data, dataSize, timeout);
}

void Delay_In_Milis(uint32_t delay)
{
	HAL_Delay(delay);
}

void I2C_Reinit_For_LCD(void)
{
	HAL_I2C_DeInit(i2cForLCDPtr);
	Delay_In_Milis(50);
	HAL_I2C_Init(i2cForLCDPtr);
}

void Delays_us(const uint16_t us_time)
{
	__HAL_TIM_SET_COUNTER(microsecondTimerPtr, 0);
	while (__HAL_TIM_GET_COUNTER(microsecondTimerPtr) < us_time)
		;
}
