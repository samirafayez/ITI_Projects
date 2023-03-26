/*
 * KEYPAD_Cfg.h
 *
 * Created: 2/3/2023 11:40:12 AM
 *  Author: HP
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

/* KEYPAD_Dimension :
*  
* Can Handle up to 4x4 only
*   
*/
#define KEYPAD_Rows 4
#define KEYPAD_Cols 3

/* KEYPAD_Pins :
*  DIO_enuPin0
*  DIO_enuPin1
*  DIO_enuPin2
*  ...
*/

#define KEYPAD_Rowpin0     DIO_enuPin0
#define KEYPAD_Rowpin1     DIO_enuPin1
#define KEYPAD_Rowpin2     DIO_enuPin2
#define KEYPAD_Rowpin3     DIO_enuPin3

#define KEYPAD_Colpin0     DIO_enuPin16
#define KEYPAD_Colpin1     DIO_enuPin17
#define KEYPAD_Colpin2     DIO_enuPin18
#define KEYPAD_Colpin3     DIO_enuPin19


#endif /* KEYPAD_CFG_H_ */