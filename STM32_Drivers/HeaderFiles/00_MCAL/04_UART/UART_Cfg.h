/*
 * UART_Cfg.h
 *
 *  Created on: Apr 7, 2023
 *      Author: HP
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_


#include "std_defines.h"


#define F_CPU 250000000




typedef enum{

	UART_enuNormalMode=0,
	UART_enuSmartCard
}UART_tenuUARTMode;


typedef enum{
	UART_enuSynchronous=0,
	UART_enuAsynchronous
}UART_tenuConnectionType;

typedef enum{

	UART_enu8Characters=0,
	UART_enu9Characters
}UART_tenuCharactersNumber;


typedef enum{

	UART_enuParityDisabled=0,
	UART_enuOddParity,
	UART_enuEvenParity
}UART_tenuParity;


typedef enum{
	UART_enuDisabled=0,
	UART_enuEnabled
}UART_tenuEN;


typedef enum{
	UART_enuSampledBy16=0,
	UART_enuSampledBy8
}UART_tenuOverSampling;


typedef enum{
	UART_enuSteadyLowValue=0,
	UART_enuSteadyHighValue
}UART_tenuClkPolarity;


typedef enum{
	//UART_enu1400 = 1400,
	UART_enu2400 = 2400,
	//UART_enu4800 = 4800,
	UART_enu9600 = 9600,
	//UART_enu14_4k = 14400,
	UART_enu19_2k = 19200,
	//UART_enu28_8k = 28800,
	UART_enu38_4k = 38400,
	UART_enu57_6k = 57600,
	//UART_enu76_8k = 76800,
	UART_enu115_2k = 115200,
	UART_enu230_4k = 230400,
	UART_enu460_8k = 460800,
	UART_enu921_6k = 921600,
	UART_enu2M = 2000000,
	UART_enu3M = 3000000

}UART_tenuBaudRate;


typedef struct {
	UART_tenuEN UART_enuEN;
	UART_tenuUARTMode UART_enuUARTMode;
	UART_tenuConnectionType UART_enuConnectionType;
	UART_tenuCharactersNumber UART_enuCharactersNumber;
	UART_tenuParity UART_enuParity;
	UART_tenuBaudRate UART_enuBaudRate;
	UART_tenuOverSampling UART_enuOverSampling;
	UART_tenuClkPolarity UART_enuClkPolarity;
	//UART_tenuEN UART_enuDMAModeEN;
	u8 UART_u8StopBits : 2;


}UART_tstrUARTCfg;


#endif /* UART_CFG_H_ */
