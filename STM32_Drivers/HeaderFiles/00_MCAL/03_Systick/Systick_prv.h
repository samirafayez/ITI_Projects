/*
 * Systick_prv.h
 *
 *  Created on: Mar 25, 2023
 *      Author: HP
 */

#ifndef SYSTICK_PRV_H_
#define SYSTICK_PRV_H_


#define Systick_MAXVALUEMASK  0x00FFFFFF
#define Systick_EN   0
#define TickInt      1
#define CLKSRC       2

typedef struct{
u32 CTRL;
u32 LOAD;
u32 VAL;
u32 CALIB;

}Systick_tstrRegisters;


#define Systick_BaseAddress	((Systick_tstrRegisters*)0xE000E010)

volatile Systick_tstrRegisters * const Systick = Systick_BaseAddress;


#endif /* SYSTICK_PRV_H_ */
