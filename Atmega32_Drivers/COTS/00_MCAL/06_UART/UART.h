/*
 * UART.h
 *
 * Created: 3/18/2023 8:51:10 AM
 *  Author: HP
 */ 


#ifndef UART_H_
#define UART_H_



typedef enum{
	UART_enuOK = 0,
	UART_enuNotOK,
	UART_enuNullPtr
}UART_tenuErrorStatus;


typedef enum{
UART_enuSynchronous=0,
UART_enuAsynchronous
}UART_tenuMode;

typedef enum{
UART_enu5Characters=0,
UART_enu6Characters,
UART_enu7Characters,
UART_enu8Characters,
UART_enu9Characters
}UART_tenuCharactersNumber;

typedef enum{
UART_enuDisabled=0,
UART_enuEvenParity=2,
UART_enuOddParity
}UART_tenuParityMode;

typedef enum{
UART_TxDataChangedPositiveEdge=0,
UART_TxDataChangedNegativeEdge
}UART_tenuClkPolarity;


typedef enum{
UART_enu2400 = 2400,
UART_enu4800 = 4800,
UART_enu9600 = 9600,
UART_enu14_4k = 14400,
UART_enu19_2k = 19200,
UART_enu28_8k = 28800,
UART_enu38_4k = 38400,
UART_enu57_6k = 57600,
UART_enu76_8k = 76800,
UART_enu115_2k = 115200,
UART_enu230_4k = 230400,
UART_enu250k = 250000,
}UART_tenuBaudRate;

typedef enum{
UART_enu2SpeedDisabled=0,
UART_enu2SpeedEnabled
}UART_tenuDoubleSpeedEN;

typedef enum{
UART_RXComplete=0,
UART_DataRegisterEMPTY,
UART_TXComplete
}UART_tenuINTSource;

/********************************/
/*UART_enuInit Function
  Input: Void
  Output: UART_tenuErrorStatus to report error*/
/******************************/
UART_tenuErrorStatus UART_enuInit(void);

/********************************/
/*UART_enuSendAsyncByte Function
  Input: UART_u8UARTByteValue
  Output: UART_tenuErrorStatus to report error*/
/******************************/
UART_tenuErrorStatus UART_enuSendAsyncByte(u16 UART_u16UARTByteValue);

/********************************/
/*UART_enuSendSyncByte Function
  Input: UART_u8UARTByteValue
  Output: UART_tenuErrorStatus to report error*/
/******************************/
UART_tenuErrorStatus UART_enuSendSyncByte(u16 UART_u16UARTByteValue);

/********************************/
/*UART_enuRecieveAsyncByte Function
  Input: UART_u8UARTByteValue
  Output: UART_tenuErrorStatus to report error*/
/******************************/
UART_tenuErrorStatus UART_enuRecieveAsyncByte(u16 * UART_u16UARTByteValue);

/********************************/
/*UART_enuRecieveSyncByte Function
  Input: UART_u8UARTByteValue
  Output: UART_tenuErrorStatus to report error*/
/******************************/
UART_tenuErrorStatus UART_enuRecieveSyncByte(u16 * UART_u16UARTByteValue);

/********************************/
/*UART_enuSetCallBack Function
  Input: Cpy_enuINTSource and Cpy_CallBackPtr pointer to function
  Output: UART_tenuErrorStatus to report error*/
/******************************/
UART_tenuErrorStatus UART_enuSetCallBack( UART_tenuINTSource Cpy_enuINTSource, void(*Cpy_CallBackPtr)(void));

#endif /* UART_H_ */