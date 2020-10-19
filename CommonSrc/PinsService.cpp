/*
 * PinsService.cpp
 *
 *  Created on: 15 paź 2020
 *      Author: Jacek
 */
#include <pinsService.h>
#include "stm32f1xx_hal.h"
#include "main.h"

Pins_Struct PinsConfiguration[] =
{
{ (GPIO_TypeDef*) DS18b20_GPIO_Port, DS18b20_Pin },
{ (GPIO_TypeDef*) DS18b20_GPIO_Port, DS18b20_Pin } };

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
	HAL_GPIO_WritePin(PinsConfiguration[pinNumber].port, PinsConfiguration[pinNumber].pin, (GPIO_PinState) pinState);
}

uint8_t Read_Pin(uint8_t pinNumber)
{
	if (pinNumber >= sizeof(PinsConfiguration) / sizeof(PinsConfiguration[0]))
		return 0;
	return HAL_GPIO_ReadPin(PinsConfiguration[pinNumber].port, PinsConfiguration[pinNumber].pin);
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
