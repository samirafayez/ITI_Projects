/*
 * LM35.h
 *
 * Created: 2/17/2023 4:59:53 AM
 *  Author: HP
 */ 


#ifndef LM35_H_
#define LM35_H_

#include "../../00_MCAL/03_ADC/ADC.h"

typedef enum{

	LM35_enuOK = 0,
	LM35_enuNotOK ,
	LM35_enuNullPtr
}LM35_tenuErrorStatus;




/********************************/
/*LM35_enuReadValue Function
  Input: ADC Channel Used and Pointer to save the reading value
  Output: Error status
  */
  /******************************/
LM35_tenuErrorStatus LM35_enuReadValue(ADC_tenuChannelNumber Cpy_u8ChannelNumber, u16* Add_pu8_PinValue);




#endif /* LM35_H_ */