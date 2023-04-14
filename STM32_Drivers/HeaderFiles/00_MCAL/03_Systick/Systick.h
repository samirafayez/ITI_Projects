/*
 * Systick.h
 *
 *  Created on: Mar 25, 2023
 *      Author: HP
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


typedef enum{
	Systick_enuOk=0,
	Systick_enuNotOk,
	Systick_enuNullPtr
}Systick_tenuErrorStatus;


Systick_tenuErrorStatus Systick_vidInit(void);


Systick_tenuErrorStatus Systick_vidSetTime(u32 Copy_u32MilliSecond);


Systick_tenuErrorStatus Systick_vidStart(void);


Systick_tenuErrorStatus Systick_vidRegisterCallBack( void(*Cpy_CallBackFunc)(void));



#endif /* SYSTICK_H_ */
