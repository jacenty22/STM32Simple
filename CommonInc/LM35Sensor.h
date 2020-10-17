/*
 * LM35Sensor.h
 *
 *  Created on: 17 paź 2020
 *      Author: Jacek
 */

#ifndef LM35SENSOR_H_
#define LM35SENSOR_H_

#include "temperatureCalculation.h"

#ifdef __cplusplus
extern "C"
{
#endif

	class LM35TemperatureCalculation: public TemperatureCalculation
	{
		public:
			LM35TemperatureCalculation(float supplyVoltage, float averageSlope);
			~LM35TemperatureCalculation();
			float Get_Temperature_For_Percentage_Of_Voltage(float percentage);
	};
#ifdef __cplusplus
}
#endif

#endif /* LM35SENSOR_H_ */
