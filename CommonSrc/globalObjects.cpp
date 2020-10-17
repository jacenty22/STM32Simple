/*
 * globalObjects.cpp
 *
 *  Created on: 14 paź 2020
 *      Author: Jacek
 */

#include "globalObjects.h"
#include "adcService.h"
#include "internalSensorTemperature.h"
#include "globalDefines.h"

ADCAveragingService adcService(ADC_RESOLUTION, COUNT_OF_ADC_CHANNELS,COUNT_OF_SAMPLES_PER_CHANNEL);
InternalSensorTempCalc internalTemp(SUPPLY_VOLTAGE,VOLTAGE_FOR_25_DEGREES_FOR_INTERNAL_SENSOR,DEGREES_FOR_VOLTAGE,AVERAGE_SLOPE_FOR_INTERNAL_SENSOR);
LM35TemperatureCalculation LM35Temp(SUPPLY_VOLTAGE,AVERAGE_SLOPE_FOR_LM35_SENSOR);

