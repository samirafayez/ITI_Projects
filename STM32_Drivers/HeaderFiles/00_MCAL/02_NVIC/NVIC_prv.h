/*
 * NVIC_prv.h
 *
 *  Created on: Mar 2, 2023
 *      Author: HP
 */

#ifndef NVIC_PRV_H_
#define NVIC_PRV_H_


#define PreemptPriority_CLRMask
#define SUBGroupPriority_CLRMask

#define INTERNALPERIPH_BASE	0xE0000000UL
#define NVIC_BASEADDRESS (NVIC_tstrRegisters *)(INTERNALPERIPH_BASE + 0x0000E100UL)

typedef struct {
u32 ISER[8];
u32 Reserved1[24];
u32 ICER[8];
u32 Reserved2[24];
u32 ISPR[8];
u32 Reserved3[24];
u32 ICPR[8];
u32 Reserved4[24];
u32 IABR[8];
u32 RESERVED5[57];
u32 IPR[60];

}NVIC_tstrRegisters;


#define STIR *((volatile u32*)0xE000EF00UL)

volatile NVIC_tstrRegisters * const NVIC = NVIC_BASEADDRESS;

#endif /* NVIC_PRV_H_ */
