/*
 * UART_Cfg.h
 *
 * Created: 3/18/2023 8:51:25 AM
 *  Author: HP
 */ 


#ifndef UART_CFG_H_
#define UART_CFG_H_


typedef struct {
UART_tenuMode UART_Mode;	
UART_tenuCharactersNumber UART_CharacterNumber;
UART_tenuParityMode UART_ParityMode;
UART_tenuBaudRate UART_BaudRate;
UART_tenuClkPolarity UART_ClkPolarity;
UART_tenuDoubleSpeedEN UART_DoubleSpeed;
u8 UART_StopBitNumber:2;
}UART_tstrCfg;



#endif /* UART_CFG_H_ */