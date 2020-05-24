/*
 * LCD_I2C.c
 *
 *  Created on: 29 mar 2020
 *      Author: Jacek
 */

#include "LCD_I2C.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "timer.h"
#include "string.h"
#include "stdint.h"
#include <stdarg.h>
#include <stdio.h>
#include "stdlib.h"

static void lcd_send_cmd(uint8_t cmd);
static void lcd_send_data(char data);
static void lcd_send_string(char *str);
static void lcd_send_string_2(char *str, uint8_t countOfChars);
static void Set_Blank_Line(uint8_t lineNumber);
static void Two_Lines_Separately_Service(void);
static void Multi_Line_Service(uint8_t ignoreTime);

LCD_struct LCDService;

enum displayMethod
{
	NONE_DISPLAY_MODE = 0x0, MULTILINE_MODE = 0x01, TWO_LINES_SEPARATELY_MODE = 0x02,

};

enum LCDCommands
{
	CLEAR_DISPLAY_CMD = 0x01,
	INIT_CMD = 0x30,
	FUNCTION_SET_CMD = 0x20,
	DISPLAY_ON_OFF_CMD = 0x08,
	ENTRY_MODE_CMD = 0x04,
	RETURN_HOME_CMD = 0x02,
	SHIFT_CMD = 0x10,
	SET_DDRAM_ADDRESS = 0x80,
	SET_CGRAM_ADDRESS = 0x40,
};
#define REINIT_TIME_IN_MILIS 5000
#define COMMUNICATION_OK_STATUS HAL_OK

#define SLAVE_ADDRESS_LCD 0x7E
#define COUNT_OF_LETTERS_IN_ONE_LINE 16
#define COUNT_OF_LINES 2

#define DUMMY_BIT 0x08
#define ENABLE_BIT 0x04
#define RESET_BIT 0x01

#define TWO_LINE_DISPLAY_MODE 0x08
#define INCREMENT_DDRAM_ADDRESS 0x02
#define DISPLAY_ON_BIT 0x04
#define SHIFT_CURSOT_TO_THE_LEFT 0x0
#define SHIFT_CURSOT_TO_THE_RIGTH 0x04

#define SECOND_LINE_ADDRESS_OFFSET 0x40
#define MAX_COUNT_OF_CHARACTERS_IN_GCRAM 8
const char ownCharacters[9][8] =	//8 znaków po 8 bajtów na każdy; w komentarzu zapis ósemkowy
		{
		{ 0x0, 0x0, 0x0E, 0x01, 0x0F, 0x11, 0x0F, 0x04 },			//ą	//\245,
				{ 0x2, 0x04, 0x0E, 0x10, 0x10, 0x11, 0x0E, 0x0 },	//ć	//\206,
				{ 0x0, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E, 0x01 },	//ę	//\251,
				{ 0x0C, 0x04, 0x06, 0x04, 0x0C, 0x04, 0x0C, 0x0 },	//ł	//\210,
				{ 0x02, 0x04, 0x16, 0x19, 0x11, 0x11, 0x11, 0x0 },	//ń	//\344
				{ 0x02, 0x04, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x0 },	//ó	//\242
				{ 0x2, 0x04, 0x0E, 0x10, 0x0E, 0x01, 0x1E, 0x0 },	//ś	//\230
				{ 0x02, 0x04, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x0 },	//ź	//\253
				{ 0x04, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x0 },	//ż	//\276
		};

static void Set_Own_Characters(void)
{
	lcd_send_cmd(SET_CGRAM_ADDRESS);
	for (uint8_t j = 0; j < sizeof(ownCharacters) / sizeof(ownCharacters[0]) && j < MAX_COUNT_OF_CHARACTERS_IN_GCRAM; j++)
	{
		for (uint8_t i = 0; i < sizeof(ownCharacters[0]) / sizeof(ownCharacters[0][0]); i++)
		{
			lcd_send_data(ownCharacters[j][i]);
		}
	}
}
void LCD_I2C_Init(void)
{
	// 4 bit initialisation
	HAL_Delay(100); // wait for >40ms
	lcd_send_cmd(INIT_CMD);
	HAL_Delay(10); // wait for >4.1ms
	lcd_send_cmd(INIT_CMD);
	HAL_Delay(1); // wait for >100us
	lcd_send_cmd(INIT_CMD);
	HAL_Delay(50);
	lcd_send_cmd(FUNCTION_SET_CMD); // 4bit mode
	HAL_Delay(50);

	lcd_send_cmd(FUNCTION_SET_CMD | TWO_LINE_DISPLAY_MODE); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(10);
	lcd_send_cmd(DISPLAY_ON_OFF_CMD); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(10);
	lcd_send_cmd(CLEAR_DISPLAY_CMD); // clear display
	HAL_Delay(10);
	lcd_send_cmd(ENTRY_MODE_CMD | INCREMENT_DDRAM_ADDRESS); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(10);
	lcd_send_cmd(DISPLAY_ON_OFF_CMD | DISPLAY_ON_BIT); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	HAL_Delay(10);
	LCD_Clear();
	HAL_Delay(100);
	Set_Own_Characters();
}

void LCD_Set_Shifting_Time(uint16_t time)
{
	LCDService.shiftTime = time;
}

void LCD_Print_With_Position(char *str, uint8_t lineNumber, uint8_t position)
{
	if (lineNumber >= COUNT_OF_LINES || position >= COUNT_OF_LETTERS_IN_ONE_LINE || LCDService.communicationStatus != COMMUNICATION_OK_STATUS)
		return;

	if (lineNumber)
		lcd_send_cmd(SET_DDRAM_ADDRESS | SECOND_LINE_ADDRESS_OFFSET | position);
	else
		lcd_send_cmd(SET_DDRAM_ADDRESS | position);
	lcd_send_string(str);
	LCDService.displayMode = NONE_DISPLAY_MODE;

	memset(LCDService.firstLineString, 0, sizeof(LCDService.firstLineString));
	memset(LCDService.secondLineString, 0, sizeof(LCDService.secondLineString));
	free(LCDService.multilineString);
}
void LCD_Print_MultiLines(char *format, ...)
{
	if (LCDService.communicationStatus != COMMUNICATION_OK_STATUS)
		return;
	va_list args;
	uint16_t textLength = 0;
	va_start(args, format);
	free(LCDService.multilineString);
	textLength = vsnprintf(NULL, 0, format, args);
	LCDService.multilineString = (char*) malloc((textLength + 1) * sizeof(char*));
	vsnprintf(LCDService.multilineString, textLength + 1, format, args);
	va_end(args);

	LCD_Clear();
	LCDService.displayMode = MULTILINE_MODE;
	memset(LCDService.secondLineString, 0, sizeof(LCDService.secondLineString));
	memset(LCDService.firstLineString, 0, sizeof(LCDService.firstLineString));
	LCDService.firstLinePrintPosition = 0;
	LCDService.secondLinePrintPosition = 0;
	LCDService.multilinePrintPosition = 0;
	LCDService.previousMilisecond = Get_Sys_Time();
	Multi_Line_Service(1);
}

void LCD_Print_In_Separately_Line(char *textToPrint, uint8_t lineNumber)
{
	if (lineNumber >= COUNT_OF_LINES || LCDService.communicationStatus != COMMUNICATION_OK_STATUS)
		return;

	if (LCDService.displayMode != TWO_LINES_SEPARATELY_MODE)
	{
		LCDService.displayMode = TWO_LINES_SEPARATELY_MODE;
		memset(LCDService.firstLineString, 0, sizeof(LCDService.firstLineString));
		memset(LCDService.secondLineString, 0, sizeof(LCDService.secondLineString));
	}

	Set_Blank_Line(lineNumber);
	lcd_send_cmd(RETURN_HOME_CMD);
	if (lineNumber == 1)
	{
		lcd_send_cmd(SET_DDRAM_ADDRESS | SECOND_LINE_ADDRESS_OFFSET);
	}

	if (!lineNumber)
	{
		if (strlen(textToPrint) > COUNT_OF_LETTERS_IN_ONE_LINE)
		{
			if (strlen(textToPrint) > ONE_LINE_MAX_LENGTH)
			{
				memcpy(LCDService.firstLineString, textToPrint,
				ONE_LINE_MAX_LENGTH);
				LCDService.firstLineString[ONE_LINE_MAX_LENGTH - 1] = '\0';
			}
			else
			{
				strcpy(LCDService.firstLineString, textToPrint);
			}
			LCDService.firstLinePrintPosition = 0;
		}
		else
		{
			memset(LCDService.firstLineString, 0, sizeof(LCDService.firstLineString));
		}
	}
	else
	{
		if (strlen(textToPrint) > COUNT_OF_LETTERS_IN_ONE_LINE)
		{
			if (strlen(textToPrint) > ONE_LINE_MAX_LENGTH)
			{
				memcpy(LCDService.secondLineString, textToPrint,
				ONE_LINE_MAX_LENGTH);
				LCDService.secondLineString[ONE_LINE_MAX_LENGTH - 1] = '\0';
			}
			else
			{
				strcpy(LCDService.secondLineString, textToPrint);
			}
			LCDService.firstLinePrintPosition = 0;
			LCDService.secondLinePrintPosition = 0;
		}
		else
		{
			memset(LCDService.secondLineString, 0, sizeof(LCDService.secondLineString));
		}
	}

	if (strlen(textToPrint) >= COUNT_OF_LETTERS_IN_ONE_LINE)
	{
		lcd_send_string_2(textToPrint, COUNT_OF_LETTERS_IN_ONE_LINE);
	}
	else
	{
		lcd_send_string(textToPrint);
	}

	LCDService.previousMilisecond = Get_Sys_Time();
}

void LCD_Clear(void)
{
	if (LCDService.communicationStatus == COMMUNICATION_OK_STATUS)
		lcd_send_cmd(CLEAR_DISPLAY_CMD);
}

void LCD_Service(void)
{
	uint8_t static communicationErrorWasActive = 0;
	if (LCDService.communicationStatus != COMMUNICATION_OK_STATUS)
	{
		if (LCDService.displayMode != NONE_DISPLAY_MODE)
		{
			LCDService.firstLinePrintPosition = 0;
			LCDService.secondLinePrintPosition = 0;
			LCDService.multilinePrintPosition = 0;
			LCDService.displayMode = NONE_DISPLAY_MODE;
			memset(LCDService.firstLineString, 0, sizeof(LCDService.firstLineString));
			memset(LCDService.secondLineString, 0, sizeof(LCDService.secondLineString));
			free(LCDService.multilineString);
		}
		if (Get_Sys_Time() - LCDService.previousMilisecond > REINIT_TIME_IN_MILIS)
		{
			LCDService.previousMilisecond = Get_Sys_Time();
			HAL_I2C_DeInit(&hi2c1);
			HAL_Delay(100);
			HAL_I2C_Init(&hi2c1);
			LCD_I2C_Init();
		}
		communicationErrorWasActive = 1;
		return;
	}
	else if (communicationErrorWasActive)
	{
		communicationErrorWasActive = 0;
		HAL_I2C_DeInit(&hi2c1);
		HAL_Delay(100);
		HAL_I2C_Init(&hi2c1);
		LCD_I2C_Init();
		return;
	}
	if (LCDService.displayMode == TWO_LINES_SEPARATELY_MODE)
	{
		Two_Lines_Separately_Service();
	}
	else if (LCDService.displayMode == MULTILINE_MODE)
	{
		Multi_Line_Service(0);
	}
}

static void lcd_send_cmd(uint8_t cmd)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd & 0xf0);
	data_l = ((cmd << 4) & 0xf0);
	data_t[0] = data_u | (DUMMY_BIT | ENABLE_BIT); //en=1, rs=0
	data_t[1] = data_u | DUMMY_BIT;				   //en=0, rs=0
	data_t[2] = data_l | (DUMMY_BIT | ENABLE_BIT); //en=1, rs=0
	data_t[3] = data_l | DUMMY_BIT;				   //en=0, rs=0
	LCDService.communicationStatus = HAL_I2C_Master_Transmit(&hi2c1,
	SLAVE_ADDRESS_LCD, (uint8_t*) data_t, 4, 200);
	if (cmd == CLEAR_DISPLAY_CMD || cmd == RETURN_HOME_CMD)
		HAL_Delay(6);
	else
		HAL_Delay(1);
}

static void lcd_send_data(char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data & 0xf0);
	data_l = ((data << 4) & 0xf0);
	data_t[0] = data_u | (DUMMY_BIT | ENABLE_BIT | RESET_BIT); //en=1, rs=1
	data_t[1] = data_u | (DUMMY_BIT | RESET_BIT);			   //en=0, rs=1
	data_t[2] = data_l | (DUMMY_BIT | ENABLE_BIT | RESET_BIT); //en=1, rs=1
	data_t[3] = data_l | (DUMMY_BIT | RESET_BIT);			   //en=0, rs=1
	LCDService.communicationStatus = HAL_I2C_Master_Transmit(&hi2c1,
	SLAVE_ADDRESS_LCD, (uint8_t*) data_t, 4, 200);
}

static void lcd_send_string(char *str)
{
	uint8_t index = 0;
	while (str[index])
	{
		switch (str[index])
		{
		case '\245':
			//Set_Own_Character(0);
			lcd_send_data(0x0);
			break;
		case '\206':
			//Set_Own_Character(1);
			lcd_send_data(0x01);
			break;
		case '\251':
			//Set_Own_Character(2);
			lcd_send_data(0x02);
			break;
		case '\210':
			//Set_Own_Character(3);
			lcd_send_data(0x03);
			break;
		case '\344':
			//Set_Own_Character(4);
			lcd_send_data(0x04);
			break;
		case '\242':
			//Set_Own_Character(5);
			lcd_send_data(0x05);
			break;
		case '\230':
			//Set_Own_Character(6);
			lcd_send_data(0x06);
			break;
		case '\253':
			//Set_Own_Character(7);
			lcd_send_data(0x07);
			break;
		case '\276':
			//Set_Own_Character(8);
			lcd_send_data(0x07);
			break;
		default:
			lcd_send_data(str[index]);
			break;
		}
		index++;
	}
}

static void lcd_send_string_2(char *str, uint8_t countOfChars)
{
	while (countOfChars)
	{
		lcd_send_data(*str++);
		countOfChars--;
	}
}

static void Set_Blank_Line(uint8_t lineNumber)
{
	if (lineNumber == 1)
	{
		lcd_send_cmd(SET_DDRAM_ADDRESS | SECOND_LINE_ADDRESS_OFFSET);
	}
	else
	{
		lcd_send_cmd(RETURN_HOME_CMD);
	}
	for (uint8_t i = 0; i < COUNT_OF_LETTERS_IN_ONE_LINE; i++)
	{
		lcd_send_string(" ");
	}
}

static void Two_Lines_Separately_Service(void)
{
	if (LCDService.shiftTime == 0)
		return;
	if (Get_Sys_Time() - LCDService.previousMilisecond >= LCDService.shiftTime)
	{
		LCDService.previousMilisecond = Get_Sys_Time();
		if (LCDService.firstLineString[0] != 0)
		{
			LCDService.firstLinePrintPosition++;
			if (LCDService.firstLinePrintPosition + COUNT_OF_LETTERS_IN_ONE_LINE > strlen(LCDService.firstLineString))
			{
				LCDService.firstLinePrintPosition = 0;
			}
			lcd_send_cmd(RETURN_HOME_CMD);
			lcd_send_string_2(LCDService.firstLineString + LCDService.firstLinePrintPosition,
			COUNT_OF_LETTERS_IN_ONE_LINE);
		}
		if (LCDService.secondLineString[0] != 0)
		{
			LCDService.secondLinePrintPosition++;
			if (LCDService.secondLinePrintPosition + COUNT_OF_LETTERS_IN_ONE_LINE > strlen(LCDService.secondLineString))
			{
				LCDService.secondLinePrintPosition = 0;
			}
			lcd_send_cmd(SET_DDRAM_ADDRESS | SECOND_LINE_ADDRESS_OFFSET);
			lcd_send_string_2(LCDService.secondLineString + LCDService.secondLinePrintPosition,
			COUNT_OF_LETTERS_IN_ONE_LINE);
		}
	}
}
static void Multi_Line_Service(uint8_t ignoreTime)
{
	uint8_t secondLine = 0, charCounter = 0;
	if (LCDService.shiftTime == 0 || LCDService.multilineString == NULL)
	{
		return;
	}
	if (Get_Sys_Time() - LCDService.previousMilisecond >= LCDService.shiftTime || ignoreTime)
	{
		LCDService.previousMilisecond = Get_Sys_Time();
		LCD_Clear();
		for (uint8_t i = LCDService.multilinePrintPosition; i < strlen(LCDService.multilineString); i++)
		{
			if (!secondLine) //zapisujemy pozycję, od której zaczniemy drukowanie po upływie czasu wypisania kolejnej linii
			{
				LCDService.multilinePrintPosition = i + 1;
			}
			if (LCDService.multilineString[i] == '\n')
			{
				charCounter = 0;
				if (!secondLine)
					lcd_send_cmd(SET_DDRAM_ADDRESS | SECOND_LINE_ADDRESS_OFFSET);
				secondLine++;
				continue;
			}
			else if (charCounter == COUNT_OF_LETTERS_IN_ONE_LINE)
			{
				charCounter = 0;
				if (!secondLine)
					lcd_send_cmd(SET_DDRAM_ADDRESS | SECOND_LINE_ADDRESS_OFFSET);
				secondLine++;
			}
			if (secondLine >= 2)
				break;
			lcd_send_data(LCDService.multilineString[i]);
			charCounter++;
		}
		if (LCDService.multilinePrintPosition + charCounter >= strlen(LCDService.multilineString))
		{
			LCDService.multilinePrintPosition = 0;
		}
	}
}
