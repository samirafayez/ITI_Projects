/*
 * TMR1_prv.h
 *
 * Created: 3/12/2023 12:10:50 AM
 *  Author: HP
 */ 


#ifndef TMR1_PRV_H_
#define TMR1_PRV_H_


#define TCCR1A *((volatile u8*) 0x4F)
#define WGM10  0
#define WGM11  1
#define COM1A0 6
#define TCCR1B *((volatile u8*) 0x4E)
#define WGM12  3
#define WGM13  4
#define ICNC1 7
#define ICES1 6
#define TCNT1 *((volatile u16*) 0x4C)
#define ICR1  *((volatile u16*) 0x46)
#define OCR1A *((volatile u16*) 0x4A)
#define TIMSk  *((volatile u8*) 0x59)
#define TICIE1 5
#define TOIE1  2
#define OCIE1A 4
#define TIFR   *((volatile u8*) 0x58)
#define TOV1   2
#define OCF1A  4
#define ICF1   5

#define Prescaler_CLR_MASK 0b11111000
#define Waveform_CLR_MASK_A 0b00111111
#define Waveform_CLR_MASK_B 0b11001111

#define TMR1_Disabled 0
#define TMR1_Enabled  1

#endif /* TMR1_PRV_H_ */