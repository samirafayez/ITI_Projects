/*
 * Scheduler.h
 *
 * Created: 3/23/2023 1:01:06 AM
 *  Author: HP
 */ 


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

typedef enum {
Scheduler_enuOk=0,
Scheduler_enuNotOk,
Scheduler_NullPtr
}Scheduler_tenuErrorStatus;



Scheduler_tenuErrorStatus Scheduler_vidInit(void);
Scheduler_tenuErrorStatus Scheduler_enuStart(void);
void Scheduler_enuTick(void);



#endif /* SCHEDULER_H_ */