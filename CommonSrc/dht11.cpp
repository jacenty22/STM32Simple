/*
 * dht11.cpp
 *
 *  Created on: 3 lis 2020
 *      Author: Jacek
 */
#include "dht11.h"
#include "timer.h"

const uint8_t lowStateMCUStartSignalDur = 18; //[ms]
const uint8_t highStateMCUStartSignalDur = 40; //[us]
const uint8_t responseSignalDuration = 80 + 20; //us + 20us zapasu na wykrycie stanu

const uint8_t lowStateDurationInData = 50 + 10; //[us]
const uint8_t highStateDurationForZero = 28 + 10; //[us]
const uint8_t highStateDurationForOne = 70 + 10; //[us]
const uint16_t timeForReadDataAgain = 5000; //[ms]

const uint8_t recheckTime = 5; //[us]
const uint8_t bytesToRead = 5; //40 bits

enum CommunicationStates
{
	DHT11_SET_HIGH_STATE_FOR_WAITING = 0x0,
	DHT11_WAITING_TO_START,
	DHT11_SET_LOW_STATE_FOR_START,
	DHT11_WAITING_IN_LOW_STATE_TO_START,
	DHT11_COMMUNICATION_IN_PROGRESS,
};

enum StatusOfReadedState
{
	EXPECTED_STATE_NOT_DETECTED = 0x0, EXPECTED_STATE_DETECTED,
};

enum BytesMeaningInReceivedData
{
	HUMADITY_INTEGER_BYTE = 0x0, HUMADITY_FRACTIONAL_BYTE, TEMPERATURE_INTEGER_BYTE, TEMPERATURE_FRACTIONAL_BYTE, CHECKSUM_BYTE,
};

DHT11_Service::DHT11_Service(function<uint8_t(uint8_t)> Read_Pin, function<void(const uint16_t)> Delay_us,
		function<void(uint8_t)> Set_Pin_Input, function<void(uint8_t)> Set_Pin_Output, function<void(uint8_t, uint8_t)> Write_Pin,
		function<uint32_t()> Get_Milisecond, uint8_t pinNumber)
{
	this->Read_Pin_State = Read_Pin;
	this->Delay_us = Delay_us;
	this->Set_Pin_Input = Set_Pin_Input;
	this->Set_Pin_Output = Set_Pin_Output;
	this->Write_Pin = Write_Pin;
	this->Get_Miliseconds = Get_Milisecond;
	this->pinNumber = pinNumber;
	this->communicationState = DHT11_SET_HIGH_STATE_FOR_WAITING;
}

DHT11_Service::~DHT11_Service()
{
}

float DHT11_Service::GetHumadity()
{
	return humadity;
}

float DHT11_Service::GetTemperature()
{
	return temperature;
}

void DHT11_Service::Communication_Init()
{
	Set_Pin_Output(pinNumber);
	Write_Pin(pinNumber, 1);
	previousMilisecond = Get_Miliseconds();
}

uint8_t DHT11_Service::IsStateDetectedWithTimeout(uint8_t expectedState, uint16_t timeout)
{
	uint8_t state;
	uint16_t timeElapsed = 0;
	while (timeElapsed <= timeout)
	{
		state = Read_Pin_State(pinNumber);
		if (state == expectedState)
		{
			return EXPECTED_STATE_DETECTED;
		}
		Delay_us(recheckTime);
		timeElapsed += recheckTime;
	}
	return EXPECTED_STATE_NOT_DETECTED;
}

void DHT11_Service::SetHighStateForStart()
{
	Set_Pin_Output(pinNumber);
	Write_Pin(pinNumber, 1);
	Delay_us(highStateMCUStartSignalDur);
}

void DHT11_Service::SetInputStateForReadResponse()
{
	Write_Pin(pinNumber, 0);
	Set_Pin_Input(pinNumber);
}

uint8_t DHT11_Service::GetHighStateDuration(uint8_t timeout)
{
	uint8_t timeElapsed = 0;
	while (timeElapsed <= timeout)
	{
		if (!Read_Pin_State(pinNumber))
		{
			break;
		}
		Delay_us(recheckTime);
		timeElapsed += recheckTime;
	}
	if (timeElapsed >= timeout)
	{
		return timeElapsed + 1;
	}
	return timeElapsed;
}

uint8_t DHT11_Service::GetByteFromDHT()
{
	uint8_t byte = 0;
	uint8_t highStateDuration;
	for (uint8_t bit = 0; bit < 8; bit++)
	{
		if (IsStateDetectedWithTimeout(1, lowStateDurationInData) == EXPECTED_STATE_DETECTED) //50us w stanie niskim; czekamy na stan wysoki
		{
			highStateDuration = GetHighStateDuration(highStateDurationForOne);
			if (highStateDuration >= highStateDurationForZero) //dla "skasowanego" bitu czas jest krotszy, wiec jezeli zostanie przekroczony, to mamy bit ustawiony
			{
				byte |= 0x01 << (7 - bit);
			}
		}
	}
	return byte;
}

uint8_t* DHT11_Service::ReadDataFromDHT(uint8_t dataRecevied[])
{
	for (uint8_t idx = 0; idx < bytesToRead; idx++)
	{
		dataRecevied[idx] = GetByteFromDHT();
	}
	return dataRecevied;
}

bool DHT11_Service::IsDataValid(uint8_t dataReceived[])
{
	uint8_t checksum = 0;
	uint8_t readedChecksum = dataReceived[CHECKSUM_BYTE];
	for (uint8_t idx = 0; idx < bytesToRead - 1; idx++)
	{
		checksum += dataReceived[idx];
	}
	if (checksum == readedChecksum)
	{
		return true;
	}
	return false;
}

void DHT11_Service::SetHighStateForWaiting()
{
	Set_Pin_Output(pinNumber);
	Write_Pin(pinNumber, 1);
	previousMilisecond = Get_Miliseconds();
	communicationState = DHT11_WAITING_TO_START;
}

void DHT11_Service::CheckIfEnoughTimeElapsedForWaiting()
{
	if (Get_Miliseconds() - previousMilisecond > timeForReadDataAgain)
	{
		communicationState = DHT11_SET_LOW_STATE_FOR_START;
	}
}

void DHT11_Service::SetLowStateForStart()
{
	Write_Pin(pinNumber, 0);
	Set_Pin_Input(pinNumber);
	previousMilisecond = Get_Miliseconds();
	communicationState = DHT11_WAITING_IN_LOW_STATE_TO_START;
}

void DHT11_Service::CheckIfTimeElapsedToStart()
{
	if (Get_Miliseconds() - previousMilisecond > lowStateMCUStartSignalDur)
	{
		communicationState = DHT11_COMMUNICATION_IN_PROGRESS;
	}
}

void DHT11_Service::CommunicationWithDHT()
{
	uint8_t dataReceived[bytesToRead] =
	{ 0 };
	uint8_t isStateDetected;
	isDataValid = false;
	SetHighStateForStart();
	SetInputStateForReadResponse();
	isStateDetected = IsStateDetectedWithTimeout(0, highStateMCUStartSignalDur); //czekamy na stan NISKI trwajacy 80us
	if (isStateDetected == EXPECTED_STATE_DETECTED)
	{
		isStateDetected = IsStateDetectedWithTimeout(1, responseSignalDuration); //czekamy na stan WYSOKI trwajacy 80us
		if (isStateDetected == EXPECTED_STATE_DETECTED)
		{
			isStateDetected = IsStateDetectedWithTimeout(0, responseSignalDuration); //czekamy na stan NISKI trwajacy 50us
			if (isStateDetected == EXPECTED_STATE_DETECTED)
			{
				ReadDataFromDHT(dataReceived);
				if (IsDataValid(dataReceived))
				{
					isDataValid = true;
					humadity = dataReceived[0];
					humadity += dataReceived[1]/(float)100;
					temperature = dataReceived[2];
					temperature += dataReceived[3]/(float)100;
				}
			}
		}
	}
	communicationState = DHT11_SET_HIGH_STATE_FOR_WAITING;
}

void DHT11_Service::Communication_Loop(void)
{
	switch (communicationState)
	{
		case DHT11_SET_HIGH_STATE_FOR_WAITING:
		{
			SetHighStateForWaiting();
			break;
		}
		case DHT11_WAITING_TO_START:
		{
			CheckIfEnoughTimeElapsedForWaiting();
			break;
		}
		case DHT11_SET_LOW_STATE_FOR_START:
		{
			SetLowStateForStart();
			break;
		}
		case DHT11_WAITING_IN_LOW_STATE_TO_START:
		{
			CheckIfTimeElapsedToStart();
			break;
		}
		case DHT11_COMMUNICATION_IN_PROGRESS:
		{
			CommunicationWithDHT();
			break;
		}
		default:
		{
			communicationState = DHT11_SET_HIGH_STATE_FOR_WAITING;
			break;
		}
	}
}

