/*
 * Scheduler.h
 *
 *  Created on: Mar 26, 2023
 *      Author: HP
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
