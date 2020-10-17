/*
 * HAL_Functions.h
 *
 *  Created on: May 24, 2020
 *      Author: Jacek
 */
#include "stdint.h"
#include <stddef.h>
#include "stm32f1xx_hal.h"

#ifndef INC_HAL_FUNCTIONS_H_
#define INC_HAL_FUNCTIONS_H_

#ifdef __cplusplus
 extern "C" {
#endif

void Hardware_Init(void);
uint8_t Transmit_For_LCD(uint16_t deviceAddress, uint8_t *data, size_t dataSize, uint32_t timeout);
void Delay_In_Milis(uint32_t delay);
void I2C_Reinit_For_LCD(void);
void Delays_us(const uint16_t us_time);
void Timers_Callback_Service(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif

#endif /* INC_HAL_FUNCTIONS_H_ */
