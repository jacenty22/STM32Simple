/*
 * Hal_Functions.c
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */

#include "HAL_Functions.h"
#include "main.h"

TIM_HandleTypeDef *htim1Ptr;
I2C_HandleTypeDef *hi2c1Ptr;


Pins_Struct PinsConfiguration[] =
{

{ (GPIO_TypeDef*) GPIOA, GPIO_PIN_5 },
{ (GPIO_TypeDef*) DS18B20_GPIO_Port, DS18B20_Pin }

};

void Hardware_Init(void)
{
#if defined(STM32F411xE)
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_ADC_Start_IT(&hadc1);

	htim1Ptr = &htim1;
	hi2c1Ptr = &hi2c1;
#endif

#if defined(STM32f1)

#endif
}

uint8_t Transmit_For_LCD(uint16_t deviceAddress, uint8_t *data, size_t dataSize, uint32_t timeout)
{
	return HAL_I2C_Master_Transmit(hi2c1Ptr, deviceAddress, (uint8_t*) data, dataSize, timeout);
}

void Delay_In_Milis(uint32_t delay)
{
	HAL_Delay(delay);
}

void I2C_For_LCD_Reinit(void)
{
	HAL_I2C_DeInit(hi2c1Ptr);
	HAL_Delay(200);
	HAL_I2C_Init(hi2c1Ptr);
}

void Delays_us(const uint16_t us_time)
{
	__HAL_TIM_SET_COUNTER(htim1Ptr, 0);
	while (__HAL_TIM_GET_COUNTER(htim1Ptr) < us_time)
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
