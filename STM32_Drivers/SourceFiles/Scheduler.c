/*
 * Scheduler.c
 *
 *  Created on: Mar 26, 2023
 *      Author: HP
 */


#include "std_defines.h"
#include "bit_math.h"
#include "00_Scheduler/Scheduler.h"
#include "00_Scheduler/Scheduler_Cfg.h"
#include "00_Scheduler/Scheduler_prv.h"
#include "03_Systick/Systick.h"



extern Scheduler_tsrRunnableInfo Scheduler_strRunnableInfo[Max_TasksNumber] ;

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
	Systick_vidInit();
	Systick_vidRegisterCallBack(Scheduler_enuTick);
	Systick_vidSetTime(TickTime_ms);


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
	Systick_vidStart();

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

