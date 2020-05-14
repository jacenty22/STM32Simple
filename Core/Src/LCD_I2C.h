/*
 * LCD_I2C.h
 *
 *  Created on: Mar 26, 2020
 *      Author: Jacek
 */
#include "stdint.h"
#ifndef SRC_LCD_I2C_H_
#define SRC_LCD_I2C_H_

typedef struct LCD_struct
{
	uint8_t firstLinePrintPosition;
	uint8_t secondLinePrintPosition;
	char *firstLineStringPtr;
	char *secondLineStringPtr;
	uint16_t shiftTime;
	uint8_t displayMethod;
	uint32_t previousMilisecond;
}LCD_struct;
void LCD_I2C_Init(void);
void lcd_send_string (char *str);
void lcd_send_cmd (uint8_t cmd);
void lcd_send_data (char data);


#endif /* SRC_LCD_I2C_H_ */
