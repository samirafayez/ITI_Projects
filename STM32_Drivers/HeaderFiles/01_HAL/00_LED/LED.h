/*
 * LED.h
 *
 *  Created on: Feb 23, 2023
 *      Author: HP
 */

#ifndef LED_H_
#define LED_H_

#include "LED_Cfg.h"



#define LED_ACTIVE_HIGH 0
#define LED_ACTIVE_LOW 1


#define LED_SPEED_LOW      0
#define LED_SPEED_MEDIUM   1
#define LED_SPEED_HIGH     2
#define LED_SPEED_VERYHIGH 3



typedef enum{

LED_enuOK = 0,
LED_enuNotOK ,
LED_enuNullPtr
}LED_tenuErrorStatus;


typedef enum{
LED_PORTA =0,
LED_PORTB,
LED_PORTC
}LED_tenuPortNumber;

typedef enum{
LED_enuPin0=0,
LED_enuPin1,
LED_enuPin2,
LED_enuPin3,
LED_enuPin4,
LED_enuPin5,
LED_enuPin6,
LED_enuPin7,
LED_enuPin8,
LED_enuPin9,
LED_enuPin10,
LED_enuPin11,
LED_enuPin12,
LED_enuPin13,
LED_enuPin14,
LED_enuPin15,
LED_enuNumberOfPins

}LED_tenuPins;


/********************************/
/*LEDInit Function
  Input: Void
  Output: ErrorStatus
  */
  /******************************/
LED_tenuErrorStatus LED_Init(void);


/********************************/
/*LED on Function
  Input: Pin number (range from 0-31)
  Output: ErrorStatus
  */
  /******************************/
LED_tenuErrorStatus LED_enuLEDon(LED_tenuLEDNames Cpy_u8LEDName);

/********************************/
/*LED off Function
  Input: Pin number (range from 0-31)
  Output: ErrorStatus
  */
  /******************************/
LED_tenuErrorStatus LED_enuLEDoff(LED_tenuLEDNames Cpy_u8LEDName);


/********************************/
/* LED_enuLEDToggle
  Input: Pin number (range from 0-31)
  Output: ErrorStatus
  */
  /******************************/
LED_tenuErrorStatus LED_enuLEDToggle(LED_tenuLEDNames Cpy_u8LEDName);

#endif /* LED_H_ */
