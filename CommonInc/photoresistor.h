/*
 * photoresistor.h
 *
 *  Created on: Dec 20, 2020
 *      Author: Jacek
 */

#ifndef PHOTORESISTOR_H_
#define PHOTORESISTOR_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

	using namespace std;
	class PhotoresistorResistance
	{
			public:
			float supplyVoltage;
			float adcMaxVoltage;
			uint16_t dividerResistance;
			uint16_t darkThreshold;
			float cellResistance;
			public:
			PhotoresistorResistance(float supplyVoltage,float adcMaxVoltage,uint16_t dividerResistance,uint16_t darkThreshold);
			bool Is_Brightness_Below_Threshold();
			void Calculate_Resistance_For_Voltage_Percentage(float dividerVoltage);
	};


#ifdef __cplusplus
}
#endif

#endif /* PHOTORESISTOR_H_ */
