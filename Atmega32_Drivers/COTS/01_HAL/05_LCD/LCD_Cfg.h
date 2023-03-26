/*
 * LCD_Cfg.h
 *
 * Created: 2/11/2023 4:32:05 AM
 *  Author: HP
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/* LCD_Pins :
*  DIO_enuPin0
*  DIO_enuPin1
*  DIO_enuPin2
*  ...
*/

/* 4_Bit Mode Data Pins*/
#define LCD_PinD4 DIO_enuPin4
#define LCD_PinD5 DIO_enuPin5
#define LCD_PinD6 DIO_enuPin6
#define LCD_PinD7 DIO_enuPin7

/* Control pins */
#define RS DIO_enuPin9
#define RW DIO_enuPin10
#define EN DIO_enuPin11


#endif /* LCD_CFG_H_ */