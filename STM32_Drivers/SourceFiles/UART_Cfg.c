/*
 * UART_Cfg.c
 *
 *  Created on: Apr 7, 2023
 *      Author: HP
 */


#include "04_UART/UART_Cfg.h"
#include "04_UART/UART.h"



const UART_tstrUARTCfg UART_strUARTCfg[UART_enuUARTsNumber] =
{
		[UART_enuUART1] =
		{
				.UART_enuEN = UART_enuEnabled,
				.UART_enuUARTMode = UART_enuNormalMode,
				.UART_enuConnectionType = UART_enuAsynchronous,
				.UART_enuCharactersNumber = UART_enu8Characters,
				.UART_enuParity = UART_enuOddParity,
				.UART_enuBaudRate = UART_enu9600,
				.UART_enuOverSampling = UART_enuSampledBy16,
				.UART_enuClkPolarity = UART_enuSteadyHighValue,
				//.UART_enuDMAModeEN = UART_enuDisabled,
				.UART_u8StopBits = 1

		},

		[UART_enuUART2] =
		{
				.UART_enuEN = UART_enuDisabled,
				.UART_enuUARTMode = UART_enuNormalMode,
				.UART_enuConnectionType = UART_enuAsynchronous,
				.UART_enuCharactersNumber = UART_enu8Characters,
				.UART_enuParity = UART_enuOddParity,
				.UART_enuBaudRate = UART_enu9600,
				.UART_enuOverSampling = UART_enuSampledBy16,
				.UART_enuClkPolarity = UART_enuSteadyHighValue,
				//.UART_enuDMAModeEN = UART_enuDisabled,
				.UART_u8StopBits = 1

		},

		[UART_enuUART6] =
		{
				.UART_enuEN = UART_enuDisabled,
				.UART_enuUARTMode = UART_enuNormalMode,
				.UART_enuConnectionType = UART_enuAsynchronous,
				.UART_enuCharactersNumber = UART_enu8Characters,
				.UART_enuParity = UART_enuOddParity,
				.UART_enuBaudRate = UART_enu9600,
				.UART_enuOverSampling = UART_enuSampledBy16,
				.UART_enuClkPolarity = UART_enuSteadyHighValue,
				//.UART_enuDMAModeEN = UART_enuDisabled,
				.UART_u8StopBits = 1


		},

};
