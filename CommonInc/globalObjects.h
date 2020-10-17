/*
 * globalObjects.h
 *
 *  Created on: 14 paź 2020
 *      Author: Jacek
 */

#include "stm32f1xx_hal.h"
#include "adcService.h"
#include "internalSensorTemperature.h"
#include "LM35Sensor.h"

#ifndef GLOBALOBJECTS_H_
#define GLOBALOBJECTS_H_

#ifdef __cplusplus
extern "C" {
#endif

extern ADCAveragingService adcService;
extern InternalSensorTempCalc internalTemp;
extern LM35TemperatureCalculation LM35Temp;

extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

#ifdef __cplusplus
}
#endif

#endif /* GLOBALOBJECTS_H_ */
