/*
 * temperatureCalculation.h
 *
 *  Created on: 14 paź 2020
 *      Author: Jacek
 */

#ifndef TEMPERATURECALCULATION_H_
#define TEMPERATURECALCULATION_H_

#ifdef __cplusplus
extern "C"
{
#endif

	class TemperatureCalculation
	{
		protected:
			float supplyVoltage;
			float averageSlope;
		public:
			TemperatureCalculation(float supplyVoltage, float averageSlope);
			~TemperatureCalculation();
			void Set_Supply_Voltage(float supplyVoltage);
			void Set_Average_Slope(float averageSlope);
			float Get_Supply_Voltage();
			float Get_Average_Slope();
			virtual float Get_Temperature_For_Percentage_Of_Voltage(float percentage)=0;
	};

#ifdef __cplusplus
}
#endif
#endif /* TEMPERATURECALCULATION_H_ */
