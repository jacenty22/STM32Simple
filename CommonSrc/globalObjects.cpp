/*
 * globalObjects.cpp
 *
 *  Created on: 14 paź 2020
 *      Author: Jacek
 */

#include <lm35Sensor.h>
#include "globalObjects.h"
#include "adcService.h"
#include "internalSensorTemperature.h"
#include "globalDefines.h"
#include "temperatureService.h"
#include "pinsFiltering.h"
#include "pinsService.h"
#include "timer.h"
#include "dht11.h"
#include "halFunctions.h"

ADCAveragingService adcService(ADC_RESOLUTION, COUNT_OF_ADC_CHANNELS, COUNT_OF_SAMPLES_PER_CHANNEL);
TemperatureService temperatureService(&adcService);
PinsFiltering pinsFiltering(Read_Pin, Get_Sys_Time);
DHT11_Service dht11(Read_Pin,
		Delays_us,
		Set_Pin_Output,
		Set_Pin_Input,
		Write_Pin,
		Get_Sys_Time,
		DHT11_PIN
		);

void Initialize_Global_Objects()
{
	InternalSensorTempCalc *internalTemp = new InternalSensorTempCalc(SUPPLY_VOLTAGE, VOLTAGE_FOR_25_DEGREES_FOR_INTERNAL_SENSOR,
	DEGREES_FOR_VOLTAGE, AVERAGE_SLOPE_FOR_INTERNAL_SENSOR);
	LM35TemperatureCalculation *LM35Temp = new LM35TemperatureCalculation(SUPPLY_VOLTAGE, AVERAGE_SLOPE_FOR_LM35_SENSOR);
	temperatureService.Add_Temperature_Calculation_Object(internalTemp, INTERNAL_SENSOR_INPUT);
	temperatureService.Add_Temperature_Calculation_Object(LM35Temp, LM35_SENSOR_INPUT);

	pinsFiltering.Add_Pin_To_Filtering(FIRST_BUTTON_PIN, 1000);
	pinsFiltering.Add_Pin_To_Filtering(SECOND_BUTTON_PIN, 2000);
	pinsFiltering.Add_Pin_To_Filtering(THIRD_BUTTON_PIN, 5000);
	dht11.Communication_Init();
}
