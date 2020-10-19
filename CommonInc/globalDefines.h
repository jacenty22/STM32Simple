/*
 * globalDefines.h
 *
 *  Created on: 17 paź 2020
 *      Author: Jacek
 */

#ifndef GLOBALDEFINES_H_
#define GLOBALDEFINES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define SUPPLY_VOLTAGE 3.3f
#define ADC_RESOLUTION 4095
#define VOLTAGE_FOR_25_DEGREES_FOR_INTERNAL_SENSOR  1.43
#define DEGREES_FOR_VOLTAGE 25
#define AVERAGE_SLOPE_FOR_INTERNAL_SENSOR 4.3
#define AVERAGE_SLOPE_FOR_LM35_SENSOR 10.0f
#define COUNT_OF_ADC_CHANNELS 2
#define COUNT_OF_SAMPLES_PER_CHANNEL 10
#define COUNT_OF_SAMPLES (COUNT_OF_SAMPLES_PER_CHANNEL * COUNT_OF_ADC_CHANNELS)

	typedef enum
	{
		LM35_SENSOR_INPUT = 0x0, INTERNAL_SENSOR_INPUT = 0x1
	} ADCChannelNumbers;
#ifdef __cplusplus
}
#endif

#endif /* GLOBALDEFINES_H_ */
