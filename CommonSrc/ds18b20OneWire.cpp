/*
 * DS18B20_One_Wire.c
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */
#include <ds18b20OneWire.h>
#include "stdint.h"
#include "math.h"
#include "string.h"

typedef enum
{
	CONVERT_T_CMD = 0x44, SKIP_ROM_CMD = 0xCC, READ_SCRATCHPAD_CMD = 0xBE,
} commands;

enum
{
	TEMPERATURE_LSB_BYTE = 0x0,
	TEMPERATURE_MSB_BYTE = 0x1,
	T_H_REGISTER_BYTE,
	T_L_REGISTER_BYTE,
	CONFIGURATION_REGISTER,
	RESERVED_BYTE,
	RESERVER_2_BYTE,
	RESERVED_3_BYTE,
	CRC_BYTE,

	RESPONSE_ARRAY_SIZE
};
#define TIME_TEMPERATURE_CONVERSION 800	//w milisekundach
#define TIME_REFRESH_TEMPERATURE_VALUE 5000//w milisekundach
#define RESET_ATTEMPT_INTERVAL 5000//w milisekundach
#define SIGN_BIT_NUMBER 3

D18B20_struct DS18B20Service;

static uint8_t DS18B20_Reset(void);
static void DS18B20_Write(uint8_t data);
static uint8_t DS18B20_Read(void);
static void DS18B20_Read_Scratchpad(void);
static void DS18B20_Convert_Temperature(void);

static uint8_t DS18B20_Reset(void)
{
	uint8_t response = 0;
	DS18B20Service.Set_Pin_Output(DS18B20Service.pinNumber);
	DS18B20Service.Write_Pin(DS18B20Service.pinNumber, 0);
	DS18B20Service.Delays_us(480);   // delay according to datasheet
	DS18B20Service.Set_Pin_Input(DS18B20Service.pinNumber);    // set the pin as input
	DS18B20Service.Delays_us(80);    // delay according to datasheet
	if (!(DS18B20Service.Read_Pin(DS18B20Service.pinNumber)))
		response = 1;    // if the pin is low i.e the presence pulse is detected

	DS18B20Service.Delays_us(400); // 480 us delay totally.

	return response;
}

void DS18B20_Init(void (*Set_Pin_Input)(uint8_t pinNumber),
		void (*Set_Pin_Output)(uint8_t pinNumber),
		void (*Delays_us)(uint16_t delay),
		void (*Write_Pin)(uint8_t pinNumber, uint8_t pinState),
		uint8_t (*Read_Pin)(uint8_t pinNumber),
		uint32_t (*Get_Sys_Time)(void),
		uint8_t pinNumber
		)
{
	DS18B20Service.Set_Pin_Input = Set_Pin_Input;
	DS18B20Service.Set_Pin_Output = Set_Pin_Output;
	DS18B20Service.Delays_us = Delays_us;
	DS18B20Service.Write_Pin = Write_Pin;
	DS18B20Service.Read_Pin = Read_Pin;
	DS18B20Service.pinNumber = pinNumber;
	DS18B20Service.Get_Sys_Time = Get_Sys_Time;
	DS18B20Service.currentTemperature = NAN;

	DS18B20Service.isResponseFromDevice = DS18B20_Reset();
	if (DS18B20Service.isResponseFromDevice)
	{
		DS18B20_Convert_Temperature();
	}
}

static void DS18B20_Write(uint8_t data)
{
	DS18B20Service.Set_Pin_Output(DS18B20Service.pinNumber);  // set as output

	for (int i = 0; i < 8; i++)
	{
		if ((data & (1 << i)) != 0)  // if the bit is high
		{
			DS18B20Service.Set_Pin_Output(DS18B20Service.pinNumber);  // set as output
			DS18B20Service.Write_Pin(DS18B20Service.pinNumber, 0);  // pull the pin LOW
			DS18B20Service.Delays_us(1);  // wait for 1 us
			DS18B20Service.Set_Pin_Input(DS18B20Service.pinNumber);  // set as input
			DS18B20Service.Delays_us(60);  // wait for 60 us
		}
		else  // if the bit is low
		{
			DS18B20Service.Set_Pin_Output(DS18B20Service.pinNumber);
			DS18B20Service.Write_Pin(DS18B20Service.pinNumber, 0);  // pull the pin LOW
			DS18B20Service.Delays_us(60);  // wait for 60 us
			DS18B20Service.Set_Pin_Input(DS18B20Service.pinNumber);
			DS18B20Service.Delays_us(1);  // wait for 60 us
		}
	}
}

static uint8_t DS18B20_Read(void)
{
	uint8_t value = 0;
	DS18B20Service.Set_Pin_Input(DS18B20Service.pinNumber);

	for (int i = 0; i < 8; i++)
	{
		DS18B20Service.Set_Pin_Output(DS18B20Service.pinNumber);   // set as output
		DS18B20Service.Write_Pin(DS18B20Service.pinNumber, 0);  // pull the data pin LOW
		DS18B20Service.Delays_us(2);  // wait for 2 us

		DS18B20Service.Set_Pin_Input(DS18B20Service.pinNumber);  // set as input
		if (DS18B20Service.Read_Pin(DS18B20Service.pinNumber))  // if the pin is HIGH
		{
			value |= 1 << i;  // read = 1
		}
		DS18B20Service.Delays_us(60);  // wait for 60 us
	}
	return value;
}

static void DS18B20_Read_Scratchpad(void)
{
	uint8_t responseData[RESPONSE_ARRAY_SIZE];
	memset(responseData, 0, sizeof(responseData));
	DS18B20Service.waitForReadScratchpad = 0;
	DS18B20Service.isResponseFromDevice = DS18B20_Reset();
	if (DS18B20Service.isResponseFromDevice)
	{
		DS18B20_Write(SKIP_ROM_CMD);
		DS18B20_Write(READ_SCRATCHPAD_CMD);
		for (uint8_t i = 0; i < RESPONSE_ARRAY_SIZE; i++)
		{
			responseData[i] = DS18B20_Read();
		}
		//odczyt dla 12-bitowej rozdzielczości
		DS18B20Service.currentTemperature = (float) (responseData[TEMPERATURE_LSB_BYTE] & 0x0F) / 16.0f;	//bity części ułamkowej
		DS18B20Service.currentTemperature += (float) (responseData[TEMPERATURE_LSB_BYTE] >> 4);		//bity części całkowitej mniej znaczącego bajtu
		DS18B20Service.currentTemperature += (float) ((responseData[TEMPERATURE_MSB_BYTE] << 4) & 0x70);//bity części całkowitej bardziej znaczącego bajitu
		if (responseData[TEMPERATURE_MSB_BYTE] & (0x01 << SIGN_BIT_NUMBER))	//znak (czy temp. dodatnia, czy ujemna)
		{
			DS18B20Service.currentTemperature *= -1;
		}
	}
}

static void DS18B20_Convert_Temperature(void)
{
	DS18B20Service.isResponseFromDevice = DS18B20_Reset();
	if (DS18B20Service.isResponseFromDevice)
	{
		DS18B20_Write(SKIP_ROM_CMD);
		DS18B20_Write(CONVERT_T_CMD);
		DS18B20Service.timeStamp = DS18B20Service.Get_Sys_Time();
		DS18B20Service.waitForReadScratchpad = 1;
	}
}

uint8_t Get_Temperature(float *temperature)
{
	if (!DS18B20Service.isResponseFromDevice || isnan(DS18B20Service.currentTemperature))
	{
		return 0;
	}
	*temperature = DS18B20Service.currentTemperature;
	return 1;
}

void DS18B20_Service(void)
{
	if (!DS18B20Service.isResponseFromDevice)
	{
		DS18B20Service.currentTemperature = NAN;
		DS18B20Service.waitForReadScratchpad = 0;
		if (DS18B20Service.Get_Sys_Time() - DS18B20Service.timeStamp > RESET_ATTEMPT_INTERVAL)
		{
			DS18B20_Convert_Temperature();
			DS18B20Service.timeStamp = DS18B20Service.Get_Sys_Time();
		}
	}
	else if (DS18B20Service.waitForReadScratchpad)
	{
		if (DS18B20Service.Get_Sys_Time() - DS18B20Service.timeStamp > TIME_TEMPERATURE_CONVERSION)
		{
			DS18B20_Read_Scratchpad();
			DS18B20Service.timeStamp = DS18B20Service.Get_Sys_Time();
		}
	}
	else if (DS18B20Service.Get_Sys_Time() - DS18B20Service.timeStamp > TIME_REFRESH_TEMPERATURE_VALUE)
	{
		DS18B20_Convert_Temperature();
	}
}
