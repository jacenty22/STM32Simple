/*
 * PinsService.h
 *
 *  Created on: 15 paź 2020
 *      Author: Jacek
 */

#ifndef PINSSERVICE_H_
#define PINSSERVICE_H_

#include "stm32f1xx_hal.h"

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct
	{
			GPIO_TypeDef *port;
			uint32_t pin;
	} Pins_Struct;

	typedef enum
	{
		DS18B20_PIN = 0x0, FIRST_BUTTON_PIN = 0x1, SECOND_BUTTON_PIN = 0x2, THIRD_BUTTON_PIN = 0x3, TRANSISTOR_PIN = 0x4, DHT11_PIN = 0x5
	} PinsEnumeration;
	void Initialize_Pins_Configuration(void);
	void Set_Pin_Output(uint8_t pinNumber);
	void Set_Pin_Input(uint8_t pinNumber);
	void Write_Pin(uint8_t pinNumber, uint8_t pinState);
	uint8_t Read_Pin(uint8_t pinNumber);

#ifdef __cplusplus
}
#endif

#endif /* PINSSERVICE_H_ */
