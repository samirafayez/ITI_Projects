/*
 * Scheduler_Cfg.h
 *
 * Created: 3/23/2023 1:00:50 AM
 *  Author: HP
 */ 


#ifndef SCHEDULER_CFG_H_
#define SCHEDULER_CFG_H_



#define Max_TasksNumber 2
#define TickTime_ms     2  


typedef struct
{
	char * Name;
	void (*CallBackPtrFunc)(void);
	u32 Start_Delay;
	u32 Period_ms;
}Scheduler_tsrRunnableInfo;



#endif /* SCHEDULER_CFG_H_ */