#ifndef DIO_H
#define DIO_H

#define PORTA_REG 0
#define PORTB_REG 1
#define PORTC_REG 2
#define PORTD_REG 3


typedef enum{

DIO_enuOK = 0,
DIO_enuNotOK ,
DIO_enuNullPtr
}DIO_tenuErrorStatus;


typedef enum{
DIO_enuPin0=0,
DIO_enuPin1,
DIO_enuPin2,
DIO_enuPin3,
DIO_enuPin4,
DIO_enuPin5,
DIO_enuPin6,
DIO_enuPin7,
DIO_enuPin8,
DIO_enuPin9,
DIO_enuPin10,
DIO_enuPin11,
DIO_enuPin12,
DIO_enuPin13,
DIO_enuPin14,
DIO_enuPin15,
DIO_enuPin16,
DIO_enuPin17,
DIO_enuPin18,
DIO_enuPin19,
DIO_enuPin20,
DIO_enuPin21,
DIO_enuPin22,
DIO_enuPin23,
DIO_enuPin24,
DIO_enuPin25,
DIO_enuPin26,
DIO_enuPin27,
DIO_enuPin28,
DIO_enuPin29,
DIO_enuPin30,
DIO_enuPin31,
DIO_enuNumberOfPins
	
}DIO_tenuPins;

typedef enum {
	LOW = 0,
	HIGH
	}DIO_tenuValue;

/********************************/
/*DIO Init Function
  Input: Void
  Output: DIO_tenuErrorStatus to report error*/
  /******************************/
DIO_tenuErrorStatus DIO_enuInit(void);

/********************************/
/*DIO SetPin Function
  Input: Pin number (range from 0-31)
  Output: 
  */
  /******************************/
DIO_tenuErrorStatus DIO_enuSetPin(DIO_tenuPins Cpy_u8PinNumber);

/********************************/
/*DIO ClearPin Function
  Input: Pin number (range from 0-31)
  Output: 
  */
  /******************************/
DIO_tenuErrorStatus DIO_enuClearPin(DIO_tenuPins Cpy_u8PinNumber);

/********************************/
/*DIO GetPin Function
  Input: Pin number (range from 0-31)
  Output: 
  */
  /******************************/
  
DIO_tenuErrorStatus DIO_enuGetPin(DIO_tenuPins Cpy_enuPinNumber,u8 * Add_pu8PinValue);

/*DIO SetValue Function
  Input: Value to be assigned (range from 0-31)
  Output: 
  */
  /******************************/
DIO_tenuErrorStatus DIO_enuSetValue(DIO_tenuPins Cpy_u8PinNumber,u8 DIO_u8AssignValue);

/*DIO_enuSetPinValue Function
  Input: Value to be assigned (range from 0-31)
  Output: 
  */
  /******************************/
DIO_tenuErrorStatus DIO_enuSetPinValue(DIO_tenuPins Cpy_u8PinNumber,DIO_tenuValue Cpy_u8AssignValue);


DIO_tenuErrorStatus DIO_enuTogglePin(DIO_tenuPins Cpy_u8PinNumber);

#endif /*DIO_H*/