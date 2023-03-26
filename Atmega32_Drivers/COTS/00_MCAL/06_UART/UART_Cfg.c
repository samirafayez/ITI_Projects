/*
 * UART_Cfg.c
 *
 * Created: 3/18/2023 8:51:54 AM
 *  Author: HP
 */ 

#include "../../LIB/std_defines.h"
#include "UART.h"
#include "UART_Cfg.h"


const UART_tstrCfg UART_strCfg = 
{
.UART_Mode = UART_enuAsynchronous,
.UART_CharacterNumber = UART_enu8Characters,
.UART_ParityMode = UART_enuDisabled,
.UART_BaudRate = UART_enu9600,
.UART_ClkPolarity = UART_TxDataChangedPositiveEdge,
.UART_DoubleSpeed = UART_enuDisabled,
.UART_StopBitNumber = 1
};


