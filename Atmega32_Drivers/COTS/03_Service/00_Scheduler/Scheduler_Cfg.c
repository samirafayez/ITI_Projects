/*
 * Scheduler_Cfg.c
 *
 * Created: 3/23/2023 1:00:17 AM
 *  Author: HP
 */ 

#include "../../LIB/std_defines.h"
#include "Scheduler_Cfg.h"


extern void App1(void);
extern void App2(void);

const Scheduler_tsrRunnableInfo Scheduler_strRunnableInfo[Max_TasksNumber] = 
{
	[0] = 
		{
			.Name = "GreenLed",
			.CallBackPtrFunc = App1,
			.Period_ms = 1000,
			.Start_Delay = 0
			
		},
	
	[1] =
		{
			.Name = "YellowLed",
			.CallBackPtrFunc = App2,
			.Period_ms = 2000,
			.Start_Delay = 5000
		
		},
	
};