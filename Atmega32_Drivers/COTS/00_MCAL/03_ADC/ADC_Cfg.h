/*
 * ADC_Cfg.h
 *
 * Created: 2/7/2023 6:52:41 PM
 *  Author: HP
 */ 

#ifndef ADC_CFG_H_
#define ADC_CFG_H_


/*
* ADC_ENABLE :
* ADC_ON
* ADC_OFF
*/
#define ADC_ENABLE ADC_ON 



/*
* ADC_Vref :
* VCC
* InternalVref
* NOVref
*/
#define ADC_Vref VCC


/*
* PrescalerValue :
* ADC_PS_2   
* ADC_PS_4   
* ADC_PS_8   
* ADC_PS_16  
* ADC_PS_32  
* ADC_PS_64  
* ADC_PS_128 
*/
#define ADC_PrescalerValue ADC_PS_128


/*
* ADC_AutoTriggerEN :
* ADC_ON
* ADC_OFF
*/
#define ADC_AutoTriggerEN ADC_OFF

/*
* ADC_Adjustment :
* ADC_Right
* ADC_Left
*/
#define ADC_Adjustment ADC_Right


/*
* ADC_AutoTriggerSrc :
* ADC_AnalogComparator
* ADC_ExtInterruptReq
* ADC_Timer0_CmpMatch
* ADC_Timer0_Overflow
* ADC_Timer1_CmpMatchB
* ADC_Timer1_Overflow
* ADC_Timer0_CaptureEvent
*/
#define ADC_AutoTriggerSrc ADC_FreeRunning

#endif /* ADC_CFG_H_ */