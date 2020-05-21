/*
 * temperature.h
 *
 *  Created on: May 20, 2020
 *      Author: Jacek
 */
#include "stdint.h"

#ifndef INC_TEMPERATURE_H_
#define INC_TEMPERATURE_H_

typedef struct temperature_struct
{
	float temperature;
	uint8_t valueReadedCorrectly;
	uint16_t samplesCounter;

}temperature_struct;
extern temperature_struct temperatureService;

void Temperature_Service(uint32_t adcValue);
uint8_t Get_Current_Temperature(float *temperature);
uint8_t Get_Average_Temperature(float *temperature);
#endif /* INC_TEMPERATURE_H_ */
