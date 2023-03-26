/*
 * Scheduler.c
 *
 * Created: 3/23/2023 12:59:59 AM
 *  Author: HP
 */ 


#include "../../LIB/bit_math.h"
#include "../../LIB/std_defines.h"
#include "../../00_MCAL/04_TMR0/TMR0.h"
#include "Scheduler.h"
#include "Scheduler_Cfg.h"
#include "Scheduler_prv.h"
#define F_CPU 1000000UL



extern const Scheduler_tsrRunnableInfo Scheduler_strRunnableInfo[Max_TasksNumber] ;

typedef struct
{
	Scheduler_tsrRunnableInfo * Scheduler_strRunnableInfoPtr;
	u32 Scheduler_RemainingTime;
}Scheduler_tstrTask;


Scheduler_tstrTask Scheduler_strTask [Max_TasksNumber];

Scheduler_tenuErrorStatus Scheduler_vidInit(void)
{
	Scheduler_tenuErrorStatus Loc_u8State = Scheduler_enuOk;
	u8 Loc_u8Index = 0;
	TMR0_vidInitPreCompile();
	TMR0_enuSetTickTimeMS(TickTime_ms,F_CPU);
	TMR0_OVInterruptEnable();
	TMR0_enuRegisterCallback(TMR0_enuOverflow,Scheduler_enuTick);
	
	for(Loc_u8Index = 0 ; Loc_u8Index < Max_TasksNumber ; Loc_u8Index++)
	{
		Scheduler_strTask[Loc_u8Index].Scheduler_strRunnableInfoPtr = &(Scheduler_strRunnableInfo[Loc_u8Index]);
		Scheduler_strTask[Loc_u8Index].Scheduler_RemainingTime = Scheduler_strRunnableInfo[Loc_u8Index].Start_Delay;
	}
	return Loc_u8State;
}


Scheduler_tenuErrorStatus Scheduler_enuStart(void)
{
	Scheduler_tenuErrorStatus Loc_u8State = Scheduler_enuOk;
	TMR0_enuStart();
	
	return Loc_u8State;
}



void Scheduler_enuTick(void)
{
	u8 Loc_u8Iter;
	for(Loc_u8Iter = 0; Loc_u8Iter<Max_TasksNumber; Loc_u8Iter++)
	{
		if(Scheduler_strTask[Loc_u8Iter].Scheduler_RemainingTime == 0)
		{
			if(Scheduler_strTask[Loc_u8Iter].Scheduler_strRunnableInfoPtr != NULL)
			{
				Scheduler_strTask[Loc_u8Iter].Scheduler_strRunnableInfoPtr->CallBackPtrFunc();
				Scheduler_strTask[Loc_u8Iter].Scheduler_RemainingTime = Scheduler_strTask[Loc_u8Iter].Scheduler_strRunnableInfoPtr->Period_ms;
			}
			else
			{
			}
			
		}
		else
		{
			Scheduler_strTask[Loc_u8Iter].Scheduler_RemainingTime -= TickTime_ms;
		}
		
	}
		
	
}