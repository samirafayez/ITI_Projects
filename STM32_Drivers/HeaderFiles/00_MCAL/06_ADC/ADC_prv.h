/*
 * ADC_prv.h
 *
 *  Created on: Apr 14, 2023
 *      Author: HP
 */

#ifndef ADC_PRV_H_
#define ADC_PRV_H_



typedef struct
{
	u32 ADC_SR;
	u32 ADC_CR1;
	u32 ADC_CR2;
	u32 ADC_SMPR1;
	u32 ADC_SMPR2;
	u32 ADC_JOFR[4];
	u32 ADC_HTR;
	u32 ADC_LTR;
	u32 ADC_SQR1;
	u32 ADC_SQR2;
	u32 ADC_SQR3;
	u32 ADC_JSQR;
	u32 ADC_JDR[4];
	u32 ADC_DR;
	u32 ADC_CCR;

}ADC_tstrRegisters;



volatile ADC_tstrRegisters * const ADC_REG = (ADC_tstrRegisters *)(0x40012000UL);



//ADC_SR
#define EOC      1
//ADC_CR1
#define AWDEN    23
#define JAWDEN   22
#define JDISCEN  12
#define DISCEN   11
#define JAUTO    10
#define AWDSGL   9
#define SCAN     8
#define JEOCIE   7
#define EOCIE    5
//ADC_CR2
#define SWSTART  30
#define JSWSTART 22
#define EOCS     10
#define ADON     0
#define CONT     1

#endif /* ADC_PRV_H_ */
