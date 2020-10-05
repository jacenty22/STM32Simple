/*
 * Hal_Functions.c
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */

#include "HAL_Functions.h"
#include "main.h"
#include "timer.h"

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

Pins_Struct PinsConfiguration[] =
{
		{ (GPIO_TypeDef*) DS18b20_GPIO_Port, DS18b20_Pin },
		{ (GPIO_TypeDef*) DS18b20_GPIO_Port, DS18b20_Pin }
};

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
	HAL_ADC_Start_IT(&hadc1);
#endif
}

void Timers_Callback_Service(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == MILISECOND_CALLBACK_TIMER)
	{
		Time_Service();
	}
}

void GPIOs_Callback_Service(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == THIRD_BUTTON_Pin)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}
	else
	{
		__NOP();
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
	HAL_Delay(200);
	HAL_I2C_Init(i2cForLCDPtr);
}

void Delays_us(const uint16_t us_time)
{
	__HAL_TIM_SET_COUNTER(microsecondTimerPtr, 0);
	while (__HAL_TIM_GET_COUNTER(microsecondTimerPtr) < us_time)
		;
}

void Set_Pin_Output(uint8_t pinNumber)
{
	if (pinNumber >= sizeof(PinsConfiguration) / sizeof(PinsConfiguration[0]))
		return;
	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };
	GPIO_InitStruct.Pin = PinsConfiguration[pinNumber].pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(PinsConfiguration[pinNumber].port, &GPIO_InitStruct);
}

void Set_Pin_Input(uint8_t pinNumber)
{
	if (pinNumber >= sizeof(PinsConfiguration) / sizeof(PinsConfiguration[0]))
		return;
	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };
	GPIO_InitStruct.Pin = PinsConfiguration[pinNumber].pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(PinsConfiguration[pinNumber].port, &GPIO_InitStruct);
}

void Write_Pin(uint8_t pinNumber, uint8_t pinState)
{
	if (pinNumber >= sizeof(PinsConfiguration) / sizeof(PinsConfiguration[0]))
		return;
	HAL_GPIO_WritePin(PinsConfiguration[pinNumber].port, PinsConfiguration[pinNumber].pin, pinState);
}

uint8_t Read_Pin(uint8_t pinNumber)
{
	if (pinNumber >= sizeof(PinsConfiguration) / sizeof(PinsConfiguration[0]))
		return 0;
	return HAL_GPIO_ReadPin(PinsConfiguration[pinNumber].port, PinsConfiguration[pinNumber].pin);
}
