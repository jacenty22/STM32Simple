/*
 * PinsService.cpp
 *
 *  Created on: 15 paź 2020
 *      Author: Jacek
 */
#include <pinsService.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "vector"

using namespace std;
vector<Pins_Struct> pinsConfiguration;

void Initialize_Pins_Configuration(void)
{
	pinsConfiguration.push_back(
	{ (GPIO_TypeDef*) DS18b20_GPIO_Port, DS18b20_Pin });
	pinsConfiguration.push_back(
	{ (GPIO_TypeDef*) FIRST_BUTTON_GPIO_Port, FIRST_BUTTON_Pin });
	pinsConfiguration.push_back(
	{ (GPIO_TypeDef*) SECOND_BUTTON_GPIO_Port, SECOND_BUTTON_Pin });
	pinsConfiguration.push_back(
	{ (GPIO_TypeDef*) THIRD_BUTTON_GPIO_Port, THIRD_BUTTON_Pin });
	pinsConfiguration.push_back(
	{ (GPIO_TypeDef*) TRANSISTOR_BASE_GPIO_Port, TRANSISTOR_BASE_Pin });
	pinsConfiguration.push_back(
		{ (GPIO_TypeDef*) DHT11_GPIO_Port, DHT11_Pin });
}

void Set_Pin_Output(uint8_t pinNumber)
{
	if (pinNumber >= pinsConfiguration.size())
		return;
	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };
	GPIO_InitStruct.Pin = pinsConfiguration[pinNumber].pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(pinsConfiguration[pinNumber].port, &GPIO_InitStruct);
}

void Set_Pin_Input(uint8_t pinNumber)
{
	if (pinNumber >= pinsConfiguration.size())
		return;
	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };
	GPIO_InitStruct.Pin = pinsConfiguration[pinNumber].pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(pinsConfiguration[pinNumber].port, &GPIO_InitStruct);
}

void Write_Pin(uint8_t pinNumber, uint8_t pinState)
{
	if (pinNumber >= pinsConfiguration.size())
		return;
	HAL_GPIO_WritePin(pinsConfiguration[pinNumber].port, pinsConfiguration[pinNumber].pin, (GPIO_PinState) pinState);
}

uint8_t Read_Pin(uint8_t pinNumber)
{
	if (pinNumber >= pinsConfiguration.size())
		return 0;
	return HAL_GPIO_ReadPin(pinsConfiguration[pinNumber].port, pinsConfiguration[pinNumber].pin);
}
