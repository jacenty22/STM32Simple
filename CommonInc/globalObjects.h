/*
 * globalObjects.h
 *
 *  Created on: 14 paź 2020
 *      Author: Jacek
 */

#include "stm32f1xx_hal.h"
#include "adcService.h"
#include "temperatureService.h"
#include "pinsFiltering.h"
#include "dht11.h"
#include "photoresistor.h"

#ifndef GLOBALOBJECTS_H_
#define GLOBALOBJECTS_H_

#ifdef __cplusplus
extern "C"
{
#endif

	extern ADCAveragingService adcService;
	extern TemperatureService temperatureService;
	extern PinsFiltering pinsFiltering;
	extern PhotoresistorResistance photresistor;

	extern ADC_HandleTypeDef hadc1;
	extern I2C_HandleTypeDef hi2c1;
	extern TIM_HandleTypeDef htim2;
	extern TIM_HandleTypeDef htim3;
	extern DHT11_Service dht11;

	void Initialize_Global_Objects();
#ifdef __cplusplus
}
#endif

#endif /* GLOBALOBJECTS_H_ */
