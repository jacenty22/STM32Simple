/*
 * LCD_I2C.c
 *
 *  Created on: 29 mar 2020
 *      Author: Jacek
 */

#include "LCD_I2C.h"
#include "stm32f4xx_hal.h"
#include "main.h"

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

LCD_struct LCDService;

enum displayMethod
{
	NONE_DISPLAY_MODE = 0x0,
	TWO_LINES_MODE = 0x01,
	TWO_LINES_SEPARATELY_MODE = 0x02,

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
};




void lcd_send_cmd (uint8_t cmd)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|(DUMMY_BIT|ENABLE_BIT);  //en=1, rs=0
	data_t[1] = data_u|DUMMY_BIT;  //en=0, rs=0
	data_t[2] = data_l|(DUMMY_BIT|ENABLE_BIT);  //en=1, rs=0
	data_t[3] = data_l|DUMMY_BIT;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 200);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|(DUMMY_BIT|ENABLE_BIT|RESET_BIT);  //en=1, rs=1
	data_t[1] = data_u|(DUMMY_BIT|RESET_BIT);  //en=0, rs=1
	data_t[2] = data_l|(DUMMY_BIT|ENABLE_BIT|RESET_BIT);  //en=1, rs=1
	data_t[3] = data_l|(DUMMY_BIT|RESET_BIT);  //en=0, rs=1
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 200);
}

void LCD_Clear(void)
{
	lcd_send_cmd(CLEAR_DISPLAY_CMD);
}

void SetShiftingTime(uint16_t time)
{
	LCDService.shiftTime = time;
}

void LCD_I2C_Init(void)
{
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (INIT_CMD);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (INIT_CMD);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (INIT_CMD);
	HAL_Delay(20);
	lcd_send_cmd (FUNCTION_SET_CMD);  // 4bit mode
	HAL_Delay(20);

	lcd_send_cmd (FUNCTION_SET_CMD|TWO_LINE_DISPLAY_MODE); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
		HAL_Delay(2);
		lcd_send_cmd (DISPLAY_ON_OFF_CMD); //Display on/off control --> D=0,C=0, B=0  ---> display off
		HAL_Delay(2);
		lcd_send_cmd (CLEAR_DISPLAY_CMD);  // clear display
		HAL_Delay(4);
		lcd_send_cmd (ENTRY_MODE_CMD|INCREMENT_DDRAM_ADDRESS); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
		HAL_Delay(2);
		lcd_send_cmd (DISPLAY_ON_OFF_CMD|DISPLAY_ON_BIT); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
		HAL_Delay(2);
}

 void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

static void lcd_send_string_2(char *str,uint8_t countOfChars)
{
	while(countOfChars)
	{
		lcd_send_data (*str++);
		countOfChars--;
	}
}

static void Set_Blank_Line(uint8_t lineNumber)
{
	lcd_send_cmd(RETURN_HOME_CMD);
	if(!lineNumber)
	{

	}
	else if(lineNumber ==1)
	{
		for(uint8_t i=0;i<SECOND_LINE_ADDRESS_OFFSET;i++)
		{
			lcd_send_cmd(SHIFT_CMD|SHIFT_CURSOT_TO_THE_RIGTH);
		}
	}
	for(uint8_t i=0;i<COUNT_OF_LETTERS_IN_ONE_LINE;i++)
	{
		lcd_send_string(" ");
	}
}
void LCD_Print_In_Separately_Line(char *textToPrint, uint8_t lineNumber)
{
	if(lineNumber >= COUNT_OF_LINES)
		return;

	Set_Blank_Line(lineNumber);
	lcd_send_cmd(RETURN_HOME_CMD);
	if(lineNumber == 1)
	{
		for(uint8_t i=0;i<SECOND_LINE_ADDRESS_OFFSET;i++)
		{
			lcd_send_cmd(SHIFT_CMD|SHIFT_CURSOT_TO_THE_RIGTH);
		}
	}

	if(!lineNumber)
	{
		if(strlen(textToPrint) >= COUNT_OF_LETTERS_IN_ONE_LINE)
	{
		LCDService.firstLineStringPtr = textToPrint;
		LCDService.firstLinePrintPosition = 0;
	}
	else
	{
		LCDService.firstLineStringPtr = NULL;
	}
	}
	else
	{
		if(strlen(textToPrint) >= COUNT_OF_LETTERS_IN_ONE_LINE)
		{
			LCDService.secondLineStringPtr = textToPrint;
			LCDService.secondLinePrintPosition = 0;
		}
		else
		{
			LCDService.secondLineStringPtr = NULL;
		}
	}

	if(strlen(textToPrint) >= COUNT_OF_LETTERS_IN_ONE_LINE)
	{
		lcd_send_string_2(textToPrint,COUNT_OF_LETTERS_IN_ONE_LINE);
	}
	else
	{
		lcd_send_string(textToPrint);
	}

	LCDService.displayMethod = TWO_LINES_SEPARATELY_MODE;
}

void LCD_Service(void)
{
}
