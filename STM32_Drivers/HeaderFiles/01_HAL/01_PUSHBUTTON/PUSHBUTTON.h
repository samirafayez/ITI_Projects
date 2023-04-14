/*
 * PUSHBUTTON.h
 *
 *  Created on: Feb 24, 2023
 *      Author: HP
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_


#include "01_PUSHBUTTON/PUSHBUTTON_Cfg.h"


#define PUSHBUTTON_PULLDOWN  3
#define PUSHBUTTON_PULLUP    4



#define LED_SPEED_LOW      0
#define LED_SPEED_MEDIUM   1
#define LED_SPEED_HIGH     2
#define LED_SPEED_VERYHIGH 3



typedef enum{

PUSHBUTTON_enuOK = 0,
PUSHBUTTON_enuNotOK ,
PUSHBUTTON_enuNullPtr
}PUSHBUTTON_tenuErrorStatus;


typedef enum{
PUSHBUTTON_PORTA =0,
PUSHBUTTON_PORTB,
PUSHBUTTON_PORTC
}PUSHBUTTON_tenuPortNumber;

typedef enum{
PUSHBUTTON_enuPin0=0,
PUSHBUTTON_enuPin1,
PUSHBUTTON_enuPin2,
PUSHBUTTON_enuPin3,
PUSHBUTTON_enuPin4,
PUSHBUTTON_enuPin5,
PUSHBUTTON_enuPin6,
PUSHBUTTON_enuPin7,
PUSHBUTTON_enuPin8,
PUSHBUTTON_enuPin9,
PUSHBUTTON_enuPin10,
PUSHBUTTON_enuPin11,
PUSHBUTTON_enuPin12,
PUSHBUTTON_enuPin13,
PUSHBUTTON_enuPin14,
PUSHBUTTON_enuPin15,
PUSHBUTTON_enuNumberOfPins

}PUSHBUTTON_tenuPins;


PUSHBUTTON_tenuErrorStatus PUSHBUTTON_enuPUSHBUTTON_Init(void);


void PUSHBUTTON_enuPUSHBUTTON_Read(void);


PUSHBUTTON_tenuErrorStatus PUSHBUTTON_enuPUSHBUTTON_ReturnState(PUSHBUTTON_tenuPUSHBUTTONNames PUSHBUTTON_enuPUSHBUTTONName, u8* Add_pu8_PinValue);
#endif /* PUSHBUTTON_H_ */
