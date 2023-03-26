#ifndef PushButton_H
#define PushButton_H

#define PORTA_REG 0
#define PORTB_REG 1
#define PORTC_REG 2
#define PORTD_REG 3


typedef enum{

PushButton_enuOK = 0,
PushButton_enuNotOK ,
PushButton_enuNullPtr
}PushButton_tenuErrorStatus;






/********************************/
/*PushButton_Read Function
  Input: Pin number (range from 0-31)
  Output: 
  */
  /******************************/
PushButton_tenuErrorStatus PushButton_enuPushButton_Read(DIO_tenuPins Cpy_u8PinNumber,u8* Add_pu8_PinValue);



#endif /*PushButton_H*/