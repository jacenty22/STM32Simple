/*
 * HAL_Functions.h
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */
#include "stdint.h"
#include <stddef.h>

#ifndef INC_HAL_FUNCTIONS_H_
#define INC_HAL_FUNCTIONS_H_

typedef struct
{
	uint32_t port;
	uint32_t pin;
} Pins_Struct;

void Hardware_Init(void);
uint8_t Transmit_For_LCD(uint16_t deviceAddress, uint8_t *data, size_t dataSize, uint32_t timeout);
void Delay_In_Milis(uint32_t delay);
void I2C_For_LCD_Reinit(void);
void Delays_us(const uint16_t us_time);
void Set_Pin_Output(uint8_t pinNumber);
void Set_Pin_Input(uint8_t pinNumber);
void Write_Pin(uint8_t pinNumber, uint8_t pinState);
uint8_t Read_Pin(uint8_t pinNumber);

#endif /* INC_HAL_FUNCTIONS_H_ */
