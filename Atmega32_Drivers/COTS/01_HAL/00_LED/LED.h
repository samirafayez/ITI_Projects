#ifndef LED_H
#define LED_H

#define PORTA_REG 0
#define PORTB_REG 1
#define PORTC_REG 2
#define PORTD_REG 3


typedef enum{

LED_enuOK = 0,
LED_enuNotOK ,
LED_enuNullPtr
}LED_tenuErrorStatus;


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
LED_enuPin16,
LED_enuPin17,
LED_enuPin18,
LED_enuPin19,
LED_enuPin20,
LED_enuPin21,
LED_enuPin22,
LED_enuPin23,
LED_enuPin24,
LED_enuPin25,
LED_enuPin26,
LED_enuPin27,
LED_enuPin28,
LED_enuPin29,
LED_enuPin30,
LED_enuPin31,

LED_enuNumberOfPins
	
}LED_tenuPins;



/********************************/
/*LED on Function
  Input: Pin number (range from 0-31)
  Output: ErrorStatus
  */
  /******************************/
LED_tenuErrorStatus LED_enuLEDon(LED_tenuPins Cpy_u8PinNumber);

/********************************/
/*LED off Function
  Input: Pin number (range from 0-31)
  Output: ErrorStatus
  */
  /******************************/
LED_tenuErrorStatus LED_enuLEDoff(LED_tenuPins Cpy_u8PinNumber);

/********************************/

LED_tenuErrorStatus LED_enuLEDToggle(LED_tenuPins Cpy_u8PinNumber);

#endif /*DIO_H*/
