/*
 * adcService.h
 *
 *  Created on: Oct 7, 2020
 *      Author: Jacek
 */

#ifndef ADCSERVICE_H_
#define ADCSERVICE_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif
	class ADCAveragingService
	{
		public:
			ADCAveragingService(uint16_t maxResolution, uint8_t countOfChannels, uint8_t countOfSamples);
			~ADCAveragingService();
			size_t Get_ADC_Array_Size();
			uint32_t* Get_ADC_Array_Address();
			uint32_t Get_ADC_Average_Value_For_Channel(uint8_t channelNumber);
			float Get_Percentage_Of_Supply_Voltage_For_Channel(uint8_t channelNumber);
			void Copy_Filled_ADC_Buffer();
			void Update_Average_ADC_Values();
		private:
			uint32_t ADCDestBuffer[COUNT_OF_SAMPLES];
			uint32_t CopyOfADCValues[COUNT_OF_SAMPLES];
			uint32_t averageADCValues[COUNT_OF_ADC_CHANNELS];
			bool isNewDataToAveraging;
			uint16_t maxResolution;
			uint8_t countOfChannels;
			uint8_t countOfSamplesPerChannel;

	};

#ifdef __cplusplus
}
#endif
#endif /* ADCSERVICE_H_ */
