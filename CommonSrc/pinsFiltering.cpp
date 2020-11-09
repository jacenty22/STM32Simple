/*
 * pinsFiltering.cpp
 *
 *  Created on: Oct 20, 2020
 *      Author: Jacek
 */

#include "pinsFiltering.h"

PinsFiltering::PinsFiltering(function<uint8_t(uint8_t)> Read_Pin, function<uint32_t()> Get_Milisecond)
{
	this->Read_Pin_State = Read_Pin;
	this->Get_Milisecond = Get_Milisecond;
}

PinsFiltering::~PinsFiltering()
{

}

void PinsFiltering::Add_Pin_To_Filtering(uint8_t pinNumber, uint32_t filteringTime)
{
	bool pinNumberExist = false;
	for (size_t index = 0; index != pinsToFiltering.size(); index++)
	{
		if (pinsToFiltering.at(index) == pinNumber)
		{
			pinNumberExist = true;
			this->filteringTime.at(index) = filteringTime;
			break;
		}
	}
	if (!pinNumberExist)
	{
		pinsToFiltering.push_back(pinNumber);
		this->filteringTime.push_back(filteringTime);
	}
	Resize_Vectors();
}

bool PinsFiltering::Get_Filtered_Pin_State(uint8_t pinNumber)
{
	if (pinNumber >= filteredPinsStates.size())
		return false;
	return filteredPinsStates.at(pinNumber);
}

void PinsFiltering::Filter_Pins_States()
{
	bool pinState;
	for (size_t index = 0; index != pinsToFiltering.size(); index++)
	{
		pinState = (bool) Read_Pin_State(pinsToFiltering.at(index));
		if (pinState != pinsStates.at(index))
		{
			pinsStates.at(index) = pinState;
			timeStateStart.at(index) = Get_Milisecond();
		}
		if (pinState != filteredPinsStates.at(index))
		{
			if ((Get_Milisecond() - timeStateStart.at(index)) >= filteringTime.at(index))
			{
				filteredPinsStates.at(index) = pinState;
			}
		}
	}
}

void PinsFiltering::Resize_Vectors()
{
	if (previousVectorSize != pinsToFiltering.size())
	{
		previousVectorSize = pinsToFiltering.size();
		pinsStates.resize(pinsToFiltering.size(), false);
		filteredPinsStates.resize(pinsToFiltering.size(), false);
		timeStateStart.resize(pinsToFiltering.size(), 0);
	}
	if (pinsToFiltering.size() != filteringTime.size())
	{
		filteringTime.resize(pinsToFiltering.size());
	}
}

