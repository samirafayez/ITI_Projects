/*
 * LDR.h
 *
 * Created: 2/10/2023 2:48:40 AM
 *  Author: HP
 */ 


#ifndef LDR_H_
#define LDR_H_

typedef enum{

	LDR_enuOK = 0,
	LDR_enuNotOK ,
	LDR_enuNullPtr
}LDR_tenuErrorStatus;




/********************************/
/*LDR_enuReadValue Function
  Input: ADC Channel Used and Pointer to save the reading value
  Output: 
  */
  /******************************/
LDR_tenuErrorStatus LDR_enuReadValue(ADC_tenuChannelNumber Cpy_u8ChannelNumber, u16* Add_pu8_PinValue);




#endif /* LDR_H_ */