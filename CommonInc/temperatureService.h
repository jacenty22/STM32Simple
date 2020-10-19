/*
 * temperatureService.h
 *
 *  Created on: 14 paź 2020
 *      Author: Jacek
 */

#ifndef TEMPERATURESERVICE_H_
#define TEMPERATURESERVICE_H_

#include "temperatureCalculation.h"
#include "vector"
#include "cstdint"
#include "globalDefines.h"
#include "adcService.h"
#include "list"

#ifdef __cplusplus
extern "C"
{
#endif
	using namespace std;
	typedef struct
	{
			TemperatureCalculation *calculationMethod;
			ADCChannelNumbers adcChannel;
	} temperatureConversion_struct;

	typedef enum
	{
		INTERNAL_SENSOR_NR = 0x0, LM35_SENSOR_NR = 0x1,
	} SensorNumber;

	class TemperatureService
	{
		private:
			vector<temperatureConversion_struct> tempConversions;
			list<float> temperatures;
			ADCAveragingService *adcService;
		public:
			TemperatureService(ADCAveragingService *adcService);
			~TemperatureService();
			void Add_Temperature_Calculation_Object(TemperatureCalculation *temperatureCalc, ADCChannelNumbers channelNumber);
			void Update_Temperatures();
			float Get_Temperature(SensorNumber sensorNumber);
	};
#ifdef __cplusplus
}
#endif
#endif /* TEMPERATURESERVICE_H_ */
