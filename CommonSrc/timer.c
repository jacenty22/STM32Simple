/*
 * timer.c
 *
 *  Created on: 14 maj 2020
 *      Author: Jacek
 */
#include "timer.h"
#include "stdint.h"

#define INTERUPT_TIME_IN_MILIS 10
timer_struct timerService;

void Time_Service(void)
{
	timerService.miliseconds+=INTERUPT_TIME_IN_MILIS;
	if(timerService.miliseconds % 1000 == 0)
	{
		timerService.seconds++;
		if(timerService.seconds %60==0)
		{
			timerService.minutes++;
		}
	}

}
uint32_t Get_Sys_Time(void)
{
	return timerService.miliseconds;
}
uint32_t Get_Sys_Seconds(void)
{
	return timerService.seconds;
}

uint32_t Get_Sys_Minutes(void)
{
	return timerService.minutes;
}
