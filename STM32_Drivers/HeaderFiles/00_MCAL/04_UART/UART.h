/*
 * UART.h
 *
 *  Created on: Apr 7, 2023
 *      Author: HP
 */

#ifndef UART_H_
#define UART_H_




typedef enum{
	UART_enuOK = 0,
	UART_enuNotOK,
	UART_enuNullPtr
}UART_tenuErrorStatus;




typedef enum{
	UART_enuUART1=0,
	UART_enuUART2,
	UART_enuUART6,
	UART_enuUARTsNumber

}UART_tenuUARTChannel;



typedef enum{
	UART_enuRX=0,
	UART_enuTX
}UART_tenuUARTCallBackType;



UART_tenuErrorStatus UART_enuInit(void);

UART_tenuErrorStatus UART_enuSynchSend(UART_tenuUARTChannel UART_enuUARTChannel, u16 Cpy_u16UARTData);

UART_tenuErrorStatus UART_enuSynchReceive(UART_tenuUARTChannel UART_enuUARTChannel, u16 * Cpy_u16UARTData);

UART_tenuErrorStatus UART_enuAsynchSend(UART_tenuUARTChannel UART_enuUARTChannel, u16 * ZeroCpy_u16UARTData, u16 Cpyu16BufferSize);

UART_tenuErrorStatus UART_enuAsynchRecieve(UART_tenuUARTChannel UART_enuUARTChannel, u16 * ZeroCpy_u16UARTData, u16 Cpyu16BufferSize);

UART_tenuErrorStatus UART_enuSetCallBackFunc(UART_tenuUARTChannel UART_enuUARTChannel, UART_tenuUARTCallBackType UART_enuUARTCallBackType, void(*Copy_CallBackFunc)(void));

UART_tenuErrorStatus UART_enuDMAEnable(UART_tenuUARTChannel UART_enuUARTChannel);

UART_tenuErrorStatus UART_enuLINEnable(UART_tenuUARTChannel UART_enuUARTChannel);


#endif /* UART_H_ */
