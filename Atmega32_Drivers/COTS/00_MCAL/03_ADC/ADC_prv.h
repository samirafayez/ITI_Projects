/*
 * ADC_prv.h
 *
 * Created: 2/7/2023 6:52:18 PM
 *  Author: HP
 */ 


#ifndef ADC_PRV_H_
#define ADC_PRV_H_

#define ISR_ADC(ISR_number) void __vector_ ##ISR_number(void) __attribute__((signal));\
void __vector_ ##ISR_number(void)

#define ADC_FreeRunning 0
#define ADC_AnalogComparator	1
#define ADC_ExtInterruptReq		2
#define ADC_Timer0_CmpMatch		3
#define ADC_Timer0_Overflow		4
#define ADC_Timer1_CmpMatchB	5
#define ADC_Timer1_Overflow		6
#define ADC_Timer0_CaptureEvent 7

#define ADC_PS_2    2
#define ADC_PS_4    4
#define ADC_PS_8    8
#define ADC_PS_16   16
#define ADC_PS_32   32
#define ADC_PS_64   64
#define ADC_PS_128  128


#define ADC_ON 1
#define ADC_OFF 0
#define VCC 0
#define InternalVref 1
#define NOVref 2
#define ADC_Right 0
#define ADC_Left 1
#define ADC_ADMUX_CLR_MASK 0b11100000
#define ADC_AutoTrigger_CLR_MASK 0b00011111


#define ADMUX *((volatile u8 *) 0x27)
#define REFS0 6
#define REFS1 7
#define ADLAR 5

#define ADCSRA *((volatile u8 *) 0x26)
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE 3
#define ADIF 4
#define ADATE 5
#define ADSC 6
#define ADEN 7

#define SFIOR *((volatile u8 *)0x50)

#define ADCL *((volatile u8 *) 0x24)
#define ADCH *((volatile u8 *) 0x25)



#endif /* ADC_PRV_H_ */