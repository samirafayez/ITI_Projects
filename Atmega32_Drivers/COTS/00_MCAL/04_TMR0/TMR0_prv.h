/*
 * TMR0_prv.h
 *
 * Created: 2/27/2023 3:22:53 AM
 *  Author: HP
 */ 


#ifndef TMR0_PRV_H_
#define TMR0_PRV_H_


#define TMR0_NoClkSrc          0
#define TMR0_NoPrescaling      1
#define TMR0_PrescalerCLK_8    2
#define TMR0_PrescalerCLK_64   3
#define TMR0_PrescalerCLK_256  4
#define TMR0_PrescalerCLK_1024 5
#define TMR0_ExtCLKSrc_FE      6
#define TMR0_ExtCLKSrc_RE      7

#define TMR0_Normal           0
#define TMR0_CTC              1
#define TMR0_FASTPWM          2
#define TMR0_PHASECORRECTPWM  3

#define OC0_NORMAL  0
#define OC0_TOGGLE  1
#define OC0_CLEAR   2
#define OC0_SET     3


#define OC0_NONINVERTING 2
#define OC0_INVERTING    3

#define OC0_CLEARONUPCOUNT 2
#define OC0_SETONUPCOUNT   3


#define TCCR0  *((volatile u8 *)0x53)
#define WGM00 6
#define WGM01 3
#define COM00 4
#define FOC0  7


#define TCNT0  *((volatile u8 *)0x52)
#define OCR0   *((volatile u8 *)0x5C)
#define TIMSK  *((volatile u8 *)0x59)
#define TOIE0 0
#define OCIE0 1
#define TIFR   *((volatile u8 *)0x58)
#define SFIOR  *((volatile u8 *)0x50)

#define Prescaler_CLR_MASK 0b11111000
#define Waveform_CLR_MASK  0b11001111


#endif /* TMR0_PRV_H_ */