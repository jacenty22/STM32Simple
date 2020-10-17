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
		DS18B20_PIN = 0x0,

	} PinNumbers;
	void Set_Pin_Output(uint8_t pinNumber);
	void Set_Pin_Input(uint8_t pinNumber);
	void Write_Pin(uint8_t pinNumber, uint8_t pinState);
	uint8_t Read_Pin(uint8_t pinNumber);
	void GPIOs_Callback_Service(uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif /* PINSSERVICE_H_ */
