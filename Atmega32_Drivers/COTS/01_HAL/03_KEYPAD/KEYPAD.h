/*
 * KEYPAD.h
 *
 * Created: 2/3/2023 11:39:40 AM
 *  Author: HP
 */ 
#ifndef KEYPAD_H_
#define KEYPAD_H_




typedef enum{

	KEYPAD_enuOK = 0,
	KEYPAD_enuNotOK ,
	KEYPAD_enuNullPtr
}KEYPAD_tenuErrorStatus;




/********************************/
/*KEYPAD_Read Function
  Input: Pin number (range from 0-31)
  Output: 
  */
  /******************************/
KEYPAD_tenuErrorStatus KEYPAD_enuKeypadRead(u8* Add_pu8_PinValue);


#endif /* KEYPAD_H_ */