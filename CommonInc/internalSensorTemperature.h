/*
 * temperature.h
 *
 *  Created on: May 20, 2020
 *      Author: Jacek
 */
#include "stdint.h"
#include "temperatureCalculation.h"

#ifndef INC_TEMPERATURE_H_
#define INC_TEMPERATURE_H_

#ifdef __cplusplus
extern "C"
{
#endif

	class InternalSensorTempCalc: public TemperatureCalculation
	{
		private:
			float voltageForNDegrees;
			float NDegrees;
		public:
			InternalSensorTempCalc(float supplyVoltage, float voltageForNDegrees, float NDegrees, float averageSlope);
			~InternalSensorTempCalc();
			float Get_Temperature_For_Percentage_Of_Voltage(float percentage);
	};

#ifdef __cplusplus
}
#endif

#endif /* INC_TEMPERATURE_H_ */
