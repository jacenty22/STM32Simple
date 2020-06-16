/*
 * timer.h
 *
 *  Created on: 14 maj 2020
 *      Author: Jacek
 */
#include "stdint.h"

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

typedef struct timer_struct
{
	uint32_t miliseconds;
	uint32_t seconds;
	uint32_t minutes;
}timer_struct;
extern timer_struct timerService;

void Time_Service(void);
uint32_t Get_Sys_Time(void);
uint32_t Get_Sys_Seconds(void);
uint32_t Get_Sys_Minutes(void);
#endif /* INC_TIMER_H_ */
