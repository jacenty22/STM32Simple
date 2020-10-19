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
#include "temperatureService.h"
#include "LM35Sensor.h"

ADCAveragingService adcService(ADC_RESOLUTION, COUNT_OF_ADC_CHANNELS, COUNT_OF_SAMPLES_PER_CHANNEL);
TemperatureService temperatureService(&adcService);

void Initialize_Global_Objects()
{
	InternalSensorTempCalc *internalTemp = new InternalSensorTempCalc(SUPPLY_VOLTAGE, VOLTAGE_FOR_25_DEGREES_FOR_INTERNAL_SENSOR,
			DEGREES_FOR_VOLTAGE, AVERAGE_SLOPE_FOR_INTERNAL_SENSOR);
	LM35TemperatureCalculation *LM35Temp = new LM35TemperatureCalculation(SUPPLY_VOLTAGE, AVERAGE_SLOPE_FOR_LM35_SENSOR);
	temperatureService.Add_Temperature_Calculation_Object(internalTemp, INTERNAL_SENSOR_INPUT);
	temperatureService.Add_Temperature_Calculation_Object(LM35Temp, LM35_SENSOR_INPUT);
}
