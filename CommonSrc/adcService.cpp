/*
 * adcService.cpp
 *
 *  Created on: 8 paź 2020
 *      Author: Jacek
 */

#include <adcService.h>
#include "stdint.h"
#include <cstddef>
#include <cstring>
#include "globalDefines.h"

using namespace std;

ADCAveragingService::ADCAveragingService(uint16_t maxResolution)
{
	if (maxResolution == 0)
	{
		throw "Resolution must be greater than zero!";
	}
	else
	{
		this->maxResolution = maxResolution;
	}
}

ADCAveragingService::~ADCAveragingService()
{
}

size_t ADCAveragingService::Get_ADC_Array_Size()
{
	return sizeof(ADCDestBuffer) / sizeof(ADCDestBuffer[0]);
}

uint32_t* ADCAveragingService::Get_ADC_Array_Address()
{
	return ADCDestBuffer;
}

uint32_t ADCAveragingService::Get_ADC_Average_Value_For_Channel(uint8_t channelNumber)
{
	if (channelNumber >= COUNT_OF_ADC_CHANNELS)
	{
		return 0;
	}
	else
	{
		return averageADCValues[channelNumber];
	}
}

float ADCAveragingService::Get_Percentage_Of_Supply_Voltage_For_Channel(uint8_t channelNumber)
{
	if (channelNumber >= COUNT_OF_ADC_CHANNELS)
	{
		return 0;
	}
	else
	{
		return 100 * Get_ADC_Average_Value_For_Channel(channelNumber) / (float) maxResolution;
	}
}

void ADCAveragingService::Copy_Filled_ADC_Buffer()
{
	if (!isNewDataToAveraging)
	{
		isNewDataToAveraging = true;
		memcpy(CopyOfADCValues, ADCDestBuffer, sizeof(CopyOfADCValues));
	}
}

void ADCAveragingService::Update_Average_ADC_Values()
{
	if (isNewDataToAveraging)
	{
		for (uint8_t channel = 0; channel < COUNT_OF_ADC_CHANNELS; channel++)
		{
			uint32_t sumOfValues = 0;
			//sumujemy dla wybranego kanalu ADC wartosci z tablicy. Dla wskazanego kanalu pierwsza wartosc znajduje sie pod indeksem channel.
			//Przyklad: Gdy mamy 3 kanaly ADC, to dla kanalu pierwszego (channel = 0) bierzemy wartosci z tablicy spod indeksow 0, 3, 6 itd.
			for (uint8_t idx = channel; idx < COUNT_OF_SAMPLES; idx += COUNT_OF_ADC_CHANNELS)
			{
				sumOfValues += CopyOfADCValues[idx];
			}
			averageADCValues[channel] = sumOfValues / COUNT_OF_SAMPLES_PER_CHANNEL;
		}
		isNewDataToAveraging = false;
	}
}
