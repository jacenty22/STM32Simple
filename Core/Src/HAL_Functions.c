/*
 * Hal_Functions.c
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */

#include "HAL_Functions.h"
#include "main.h"

Pins_Struct PinsConfiguration[] =
{
{ GPIOA, GPIO_PIN_5 },
{ DS18B20_GPIO_Port, DS18B20_Pin } };

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
	HAL_Delay(200);
	HAL_I2C_Init(&hi2c1);
}

void Delays_us(const uint16_t us_time)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while (__HAL_TIM_GET_COUNTER(&htim1) < us_time)
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
