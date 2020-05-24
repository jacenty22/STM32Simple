/*
 * DS18B20_One_Wire.h
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */

#ifndef INC_DS18B20_ONE_WIRE_H_
#define INC_DS18B20_ONE_WIRE_H_

#include "stdint.h"

typedef struct
{
	void (*Set_Pin_Input)(uint8_t pinNumber);
	void (*Set_Pin_Output)(uint8_t pinNumber);
	void (*Delays_us)(uint16_t delay);
	void (*Write_Pin)(uint8_t pinNumber, uint8_t pinState);
	uint8_t (*Read_Pin)(uint8_t pinNumber);
	uint32_t (*Get_Sys_Time)(void);
	uint8_t isResponseFromDevice;
	uint8_t pinNumber;
	uint32_t timeStamp;
	float currentTemperature;
	uint8_t waitForReadScratchpad;
} D18B20_struct;

extern D18B20_struct DS18B20Service;

void DS18B20_Init(void (*Set_Pin_Input)(uint8_t pinNumber), void (*Set_Pin_Output)(uint8_t pinNumber), void (*Delays_us)(uint16_t delay),
		void (*Write_Pin)(uint8_t pinNumber, uint8_t pinState), uint8_t (*Read_Pin)(uint8_t pinNumber), uint32_t (*Get_Sys_Time)(void));
uint8_t Get_Temperature(float *temperature);
void DS18B20_Service(void);

#endif /* INC_DS18B20_ONE_WIRE_H_ */
