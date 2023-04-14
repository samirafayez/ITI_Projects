/*
 * Scheduler_Cfg.h
 *
 *  Created on: Mar 26, 2023
 *      Author: HP
 */

#ifndef SCHEDULER_CFG_H_
#define SCHEDULER_CFG_H_

#include "std_defines.h"
#define CLK_FREQUENCY 25000000UL



#define Max_TasksNumber 2
#define TickTime_ms     1


typedef struct
{
	char * Name;
	void (*CallBackPtrFunc)(void);
	u32 Start_Delay;
	u32 Period_ms;
}Scheduler_tsrRunnableInfo;



#endif /* SCHEDULER_CFG_H_ */
