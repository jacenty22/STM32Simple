/*
 * LCD_I2C.h
 *
 *  Created on: Mar 26, 2020
 *      Author: Jacek
 */
#include "stdint.h"
#ifndef SRC_LCD_I2C_H_
#define SRC_LCD_I2C_H_
#define ONE_LINE_MAX_LENGTH 32

typedef struct LCD_struct
{
	uint8_t firstLinePrintPosition;
	uint8_t secondLinePrintPosition;
	uint8_t multilinePrintPosition;
	uint16_t shiftTime;
	uint8_t displayMode;
	uint32_t previousMilisecond;
	char firstLineString[ONE_LINE_MAX_LENGTH];
	char secondLineString[ONE_LINE_MAX_LENGTH];
	char *multilineString;
} LCD_struct;

void LCD_I2C_Init(void);
void LCD_Service(void);
void LCD_Set_Shifting_Time(uint16_t time);
void LCD_Print_MultiLines(char *format, ...);
void LCD_Print_In_Separately_Line(char *textToPrint, uint8_t lineNumber);
void LCD_Clear(void);

#endif /* SRC_LCD_I2C_H_ */
