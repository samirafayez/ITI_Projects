/*
 * ADC.h
 *
 * Created: 2/7/2023 6:49:29 PM
 *  Author: HP
 */ 


#ifndef ADC_H_
#define ADC_H_


typedef enum {
	
	ADC_enuOk=0,
	ADC_enuNotOk,
	ADC_enuNullPtr
	
}ADC_tenuErrorStatus;



typedef enum{
	ADC_Channel0 = 0,
	ADC_Channel1,
	ADC_Channel2,
	ADC_Channel3,
	ADC_Channel4,
	ADC_Channel5,
	ADC_Channel6,
	ADC_Channel7
}ADC_tenuChannelNumber;




/********************************/
/*ADC_enuInit Function
  Input: void
  Output: Error Status */
/******************************/
ADC_tenuErrorStatus ADC_enuInit(void);

/********************************/
/*ADC_enuSelectChannel Function
  Input: Used Channel in PORTA
  Output: Error Status*/
/******************************/
ADC_tenuErrorStatus ADC_enuSelectChannel( ADC_tenuChannelNumber Cpy_u8ChannelNumber);


/********************************/
/*ADC_enuSynchGetADCValue Function
  Input: Pointer to save the Value
  Output: Error Status*/
/******************************/
ADC_tenuErrorStatus ADC_enuSynchGetADCValue(u16 * Add_pu8ADCValue);


/********************************/
/*ADC_enuASynchGetADCValue Function
  Input: Pointer to save the Value
  Output: Error Status*/
/******************************/

ADC_tenuErrorStatus ADC_enuASynchGetADCValue( u16 * Add_pu16ADCValue);


/********************************/
/*ADC_enuEnableInterrupt Function
  Input: void
  Output: Error Status*/
/******************************/
ADC_tenuErrorStatus ADC_enuEnableInterrupt(void);


/********************************/
/*ADC_enuEnableInterrupt Function
  Input: void
  Output: Error Status*/
/******************************/
ADC_tenuErrorStatus ADC_enuDisableInterrupt(void);


/********************************/
/*ADC_enuSetCallback Function
  Input: Pointer to Function
  Output: Error Status*/
/******************************/
ADC_tenuErrorStatus ADC_enuSetCallback(void(*CpyFuncPtr)(void));
#endif /* ADC_H_ */