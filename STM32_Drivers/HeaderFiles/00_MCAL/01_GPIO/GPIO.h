/*
 * GPIO.h
 *
 *  Created on: Feb 16, 2023
 *      Author: HP
 */

#ifndef GPIO_H_
#define GPIO_H_




#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2

#define GPIO_PIN_0   0
#define GPIO_PIN_1   1
#define GPIO_PIN_2   2
#define GPIO_PIN_3   3
#define GPIO_PIN_4   4
#define GPIO_PIN_5   5
#define GPIO_PIN_6   6
#define GPIO_PIN_7   7
#define GPIO_PIN_8   8
#define GPIO_PIN_9   9
#define GPIO_PIN_10  10
#define GPIO_PIN_11  11
#define GPIO_PIN_12  12
#define GPIO_PIN_13  13
#define GPIO_PIN_14  14
#define GPIO_PIN_15  15


#define GPIO_SPEED_LOW      0
#define GPIO_SPEED_MEDIUM   1
#define GPIO_SPEED_HIGH     2
#define GPIO_SPEED_VERYHIGH 3


#define GPIO_MODE_PP         0
#define GPIO_MODE_OPENDRAIN  1
#define GPIO_MODE_ANALOG	 2
#define GPIO_PIN_PD	         3
#define GPIO_PIN_PU          4
#define GPIO_MODE_ALTFUN	 5

#define AF0_SYSTEM       0
#define AF1_TIM1_TIM2    1
#define AF2_TIM3_5       2
#define AF3_TIM9_11      3
#define AF4_I2C1_3       4
#define AF5_SPI1_4       5
#define AF6_SPI3         6
#define AF7_USART1_2     7
#define AF8_USART6       8
#define AF9_I2C2_3       9
#define AF10_OTG_FS      10
#define AF12_SDIO        12
#define AF15_EVENTOUT    15


#define GPIO_HIGH    1
#define GPIO_LOW     0






typedef enum{

GPIO_enuOK = 0,
GPIO_enuNotOK ,
GPIO_enuNullPtr
}GPIO_tenuErrorStatus;



typedef struct{
u8 PORT;
u8 PIN;
u8 SPEED;
u8 MODE;
}GPIOcgf_t;



GPIO_tenuErrorStatus GPIO_Init(GPIOcgf_t * Add_pu8cfgstruct);
GPIO_tenuErrorStatus GPIO_WritePinValue(u8 Cpy_u8PortNumber, u8 Cpy_u8PinNumber, u8 Cpy_u8PinValue);
GPIO_tenuErrorStatus GPIO_SetPortValue(u8 Cpy_u8PortNumber, u16 Cpy_u8PortValue);
GPIO_tenuErrorStatus GPIO_SelectAlternateFunc(u8 Cpy_u8PortNumber, u8 Cpy_u8PinNumber, u8 Cpy_u8AlternateFunc);
GPIO_tenuErrorStatus GPIO_ReadPinValue(u8 Cpy_u8PortNumber, u8 Cpy_u8PinNumber, u8 * Add_pu8PinValue);
GPIO_tenuErrorStatus GPIO_TogglePinValue(u8 Cpy_u8PortNumber, u8 Cpy_u8PinNumber);




#endif /* GPIO_H_ */
