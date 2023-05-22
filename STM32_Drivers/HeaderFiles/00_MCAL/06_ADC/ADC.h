/*
 * ADC.h
 *
 *  Created on: Apr 14, 2023
 *      Author: HP
 */

#ifndef ADC_H_
#define ADC_H_


typedef enum
{
	ADC_enuOK=0,
	ADC_enuNotOK,
	ADC_enuNullPtr
}ADC_tenuErrorStatus;


typedef enum
{
	ADC_enuChannel1=0,
	ADC_enuChannel2,
	ADC_enuChannel3,
	ADC_enuChannel4

}ADC_tenuInjectedChannels;



ADC_tenuErrorStatus ADC_enuInit(void);
ADC_tenuErrorStatus ADC_enuStartConversion_RegularChannels(u16 * Cpy_pu16ADCValue);
ADC_tenuErrorStatus ADC_enuStartConversion_InjectedChannels(ADC_tenuInjectedChannels ADC_enuInjectedChannels, u16 * Cpy_pu16ADCValue);
ADC_tenuErrorStatus ADC_enuEnableDMA(void);


#endif /* ADC_H_ */
