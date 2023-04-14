/*
 * UART.c
 *
 *  Created on: Apr 7, 2023
 *      Author: HP
 */

#include "std_defines.h"
#include "bit_math.h"
#include "04_UART/UART.h"
#include "04_UART/UART_Cfg.h"
#include "04_UART/UART_prv.h"
#include "01_GPIO/GPIO.h"
#include "00_RCC/RCC.h"
#include "02_NVIC/NVIC.h"

#include <math.h>


#define UART_Busy 0
#define UART_Idle 1

#define UART_STOPBitsCLRMask 0xFFFFCFFF
static void (*UART_CallBackPtrRX[UART_enuUARTsNumber])(void) = {NULL};
static void (*UART_CallBackPtrTX[UART_enuUARTsNumber])(void) = {NULL};
static volatile u8 RX_Status[UART_enuUARTsNumber] = {UART_Idle};
static volatile u8 TX_Status[UART_enuUARTsNumber] = {UART_Idle};
static volatile u16 (* RX_Buffer[UART_enuUARTsNumber]) = {NULL};
static volatile u16 (* TX_Buffer[UART_enuUARTsNumber]) = {NULL};
static volatile u16 RX_BufferSize[UART_enuUARTsNumber] = {0};
static volatile u16 TX_BufferSize[UART_enuUARTsNumber] = {0};
static volatile u16 RX_Index[UART_enuUARTsNumber] = {0};
static volatile u16 TX_Index[UART_enuUARTsNumber] = {0};

extern const UART_tstrUARTCfg UART_strUARTCfg[UART_enuUARTsNumber];



UART_tenuErrorStatus UART_enuInit(void)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;

	u8 Loc_u8Iter;
	f32 Loc_f32USART_DIV = 0.0;
	u32 Loc_u32Mantissa =0;
	u8 Loc_u8Fraction =0;

	for(Loc_u8Iter = 0;Loc_u8Iter < UART_enuUARTsNumber; Loc_u8Iter++)
	{

		//Enabling the UART Channel
		if(UART_strUARTCfg[Loc_u8Iter].UART_enuEN == UART_enuDisabled)
		{
			CLR_BIT(UART[Loc_u8Iter]->USART_CR1,UE);
			CLR_BIT(UART[Loc_u8Iter]->USART_CR1,TE);
			CLR_BIT(UART[Loc_u8Iter]->USART_CR1,RE);
		}
		else if(UART_strUARTCfg[Loc_u8Iter].UART_enuEN == UART_enuEnabled)
		{
			SET_BIT(UART[Loc_u8Iter]->USART_CR1,UE);
			SET_BIT(UART[Loc_u8Iter]->USART_CR1,TE);
			SET_BIT(UART[Loc_u8Iter]->USART_CR1,RE);
			//Initializing pins
			switch(Loc_u8Iter)
			{
			case UART_enuUART1:
				RCC_Peripheral_EnableSysClk(APB2,USART1);
				NVIC_enuEnable(NVIC_USART1);
				GPIO_SelectAlternateFunc(GPIO_PORTB, GPIO_PIN_6, AF7_USART1_2);
				GPIO_SelectAlternateFunc(GPIO_PORTB, GPIO_PIN_7, AF7_USART1_2);
				break;
			case UART_enuUART2:
				RCC_Peripheral_EnableSysClk(APB1,USART2);
				NVIC_enuEnable(NVIC_USART2);
				GPIO_SelectAlternateFunc(GPIO_PORTA, GPIO_PIN_2, AF7_USART1_2);
				GPIO_SelectAlternateFunc(GPIO_PORTA, GPIO_PIN_3, AF7_USART1_2);
				break;
			case UART_enuUART6:
				RCC_Peripheral_EnableSysClk(APB2,USART6);
				NVIC_enuEnable(NVIC_USART6);
				GPIO_SelectAlternateFunc(GPIO_PORTA, GPIO_PIN_11, AF8_USART6);
				GPIO_SelectAlternateFunc(GPIO_PORTA, GPIO_PIN_12, AF8_USART6);
				break;
			}
		}
		else
		{
			Loc_u8State = UART_enuNotOK;
		}
		//Selecting mode of UART Normal or Smartcard
		if(UART_strUARTCfg[Loc_u8Iter].UART_enuUARTMode == UART_enuNormalMode)
		{
			CLR_BIT(UART[Loc_u8Iter]->USART_CR3,SCEN);
		}
		else if(UART_strUARTCfg[Loc_u8Iter].UART_enuUARTMode == UART_enuSmartCard)
		{
			SET_BIT(UART[Loc_u8Iter]->USART_CR3,SCEN);
		}
		else
		{
			Loc_u8State = UART_enuNotOK;
		}
		//Selecting connection type
		if(UART_strUARTCfg[Loc_u8Iter].UART_enuConnectionType == UART_enuAsynchronous)
		{
			CLR_BIT(UART[Loc_u8Iter]->USART_CR3, CLKEN);
		}
		else if(UART_strUARTCfg[Loc_u8Iter].UART_enuConnectionType == UART_enuSynchronous)
		{
			SET_BIT(UART[Loc_u8Iter]->USART_CR3, CLKEN);
		}
		else
		{
			Loc_u8State = UART_enuNotOK;
		}
		//Selecting word length
		if(UART_strUARTCfg[Loc_u8Iter].UART_enuCharactersNumber == UART_enu8Characters)
		{
			CLR_BIT(UART[Loc_u8Iter]->USART_CR1, M);
		}
		else if(UART_strUARTCfg[Loc_u8Iter].UART_enuCharactersNumber == UART_enu9Characters)
		{
			SET_BIT(UART[Loc_u8Iter]->USART_CR1, M);
		}
		else
		{
			Loc_u8State = UART_enuNotOK;
		}
		//Selecting Parity
		switch(UART_strUARTCfg[Loc_u8Iter].UART_enuParity)
		{
		case UART_enuParityDisabled:
			CLR_BIT(UART[Loc_u8Iter]->USART_CR1, PCE);
			break;
		case UART_enuOddParity:
			SET_BIT(UART[Loc_u8Iter]->USART_CR1, PCE);
			SET_BIT(UART[Loc_u8Iter]->USART_CR1, PS);
			break;
		case UART_enuEvenParity:
			SET_BIT(UART[Loc_u8Iter]->USART_CR1, PCE);
			CLR_BIT(UART[Loc_u8Iter]->USART_CR1, PS);
			break;
		default:
			Loc_u8State = UART_enuNotOK;
			break;
		}
		//Oversampling Selection
		if(UART_strUARTCfg[Loc_u8Iter].UART_enuOverSampling == UART_enuSampledBy16)
		{
			CLR_BIT(UART[Loc_u8Iter]->USART_CR1, OVER8);
		}
		else if(UART_strUARTCfg[Loc_u8Iter].UART_enuOverSampling == UART_enuSampledBy8)
		{
			SET_BIT(UART[Loc_u8Iter]->USART_CR1, OVER8);
		}
		else
		{
			Loc_u8State = UART_enuNotOK;
		}
		//Selecting CLK Polarity
		if(UART_strUARTCfg[Loc_u8Iter].UART_enuClkPolarity == UART_enuSteadyLowValue)
		{
			CLR_BIT(UART[Loc_u8Iter]->USART_CR2, CPOL);
		}
		else if(UART_strUARTCfg[Loc_u8Iter].UART_enuClkPolarity == UART_enuSteadyHighValue)
		{
			SET_BIT(UART[Loc_u8Iter]->USART_CR2, CPOL);
		}
		else
		{
			Loc_u8State = UART_enuNotOK;
		}
		//Selecting stop bits
		if(UART_strUARTCfg[Loc_u8Iter].UART_u8StopBits == 1)
		{
			CLR_BIT(UART[Loc_u8Iter]->USART_CR2, STOP0);
			CLR_BIT(UART[Loc_u8Iter]->USART_CR2, STOP1);
		}
		else if(UART_strUARTCfg[Loc_u8Iter].UART_u8StopBits == 2)
		{
			CLR_BIT(UART[Loc_u8Iter]->USART_CR2, STOP0);
			SET_BIT(UART[Loc_u8Iter]->USART_CR2, STOP1);
		}
		else
		{
			Loc_u8State = UART_enuNotOK;
		}

		//Baud Rate
		Loc_f32USART_DIV = (f32)F_CPU/(UART_strUARTCfg[Loc_u8Iter].UART_enuBaudRate*8*(2-UART_strUARTCfg[Loc_u8Iter].UART_enuOverSampling));
		Loc_u32Mantissa = ceil(Loc_f32USART_DIV)-1;

		if(UART_strUARTCfg[Loc_u8Iter].UART_enuOverSampling == UART_enuSampledBy16)
		{
			Loc_u8Fraction = fabs((Loc_f32USART_DIV-Loc_u32Mantissa)*16);
			if(Loc_u8Fraction > 0x0F)
			{
				Loc_u8Fraction=0;
				Loc_u32Mantissa++;
			}
			else
			{
				//Do nothing
			}
			Loc_u8Fraction &= 0x0F;
		}
		else
		{
			Loc_u8Fraction = fabs((Loc_f32USART_DIV-Loc_u32Mantissa)*8);
			if(Loc_u8Fraction > 0x0E)
			{
				Loc_u8Fraction=0;
				Loc_u32Mantissa++;
			}
			else
			{
				//Do nothing
			}
			Loc_u8Fraction &= 0x0E;
		}

		UART[Loc_u8Iter]->USART_BRR = (Loc_u32Mantissa<<4) | Loc_u8Fraction;

	}

	return Loc_u8State;
}



UART_tenuErrorStatus UART_enuSynchSend(UART_tenuUARTChannel UART_enuUARTChannel, u16 Cpy_u16UARTData)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	if(UART_enuUARTChannel<UART_enuUARTsNumber)
	{

		UART[UART_enuUARTChannel]->USART_DR = Cpy_u16UARTData;
		while(!GET_BIT(UART[UART_enuUARTChannel]->USART_SR, TXE));
		CLR_BIT(UART[UART_enuUARTChannel]->USART_SR, TXE);

	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}

	return Loc_u8State;
}




UART_tenuErrorStatus UART_enuSynchReceive(UART_tenuUARTChannel UART_enuUARTChannel, u16 * Cpy_u16UARTData)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	if((UART_enuUARTChannel<UART_enuUARTsNumber) && (Cpy_u16UARTData != NULL))
	{
		*Cpy_u16UARTData = UART[UART_enuUARTChannel]->USART_DR ;
		while(!GET_BIT(UART[UART_enuUARTChannel]->USART_SR, RXNE));
		CLR_BIT(UART[UART_enuUARTChannel]->USART_SR, RXNE);
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}


	return Loc_u8State;
}


UART_tenuErrorStatus UART_enuAsynchSend(UART_tenuUARTChannel UART_enuUARTChannel, u16 * ZeroCpy_u16UARTData, u16 Cpyu16BufferSize)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	//SET_BIT(UART[UART_enuUARTChannel]->USART_CR1, TCIE);
	SET_BIT(UART[UART_enuUARTChannel]->USART_CR1, TXEIE);
	if((UART_enuUARTChannel<UART_enuUARTsNumber) && (ZeroCpy_u16UARTData != NULL))
	{
		if(TX_Status[UART_enuUARTChannel] == UART_Idle)
		{
			TX_Index[UART_enuUARTChannel] = 0;
			TX_BufferSize[UART_enuUARTChannel] = Cpyu16BufferSize;
			TX_Buffer[UART_enuUARTChannel] = ZeroCpy_u16UARTData;
			UART[UART_enuUARTChannel]->USART_DR = *(TX_Buffer[TX_Index[UART_enuUARTChannel]]);
			TX_Status[UART_enuUARTChannel] = UART_Busy;
		}
		else
		{

		}
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}


	return Loc_u8State;
}


UART_tenuErrorStatus UART_enuAsynchRecieve(UART_tenuUARTChannel UART_enuUARTChannel, u16 * ZeroCpy_u16UARTData, u16 Cpyu16BufferSize)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	SET_BIT(UART[UART_enuUARTChannel]->USART_CR1, RXNEIE);
	if((UART_enuUARTChannel<UART_enuUARTsNumber) && (ZeroCpy_u16UARTData != NULL))
	{
		if(RX_Status[UART_enuUARTChannel] == UART_Idle)
		{
			RX_Index[UART_enuUARTChannel] = 0;
			RX_BufferSize[UART_enuUARTChannel] = Cpyu16BufferSize;
			RX_Buffer[UART_enuUARTChannel] = ZeroCpy_u16UARTData;
			*(RX_Buffer[RX_Index[UART_enuUARTChannel]]) = UART[UART_enuUARTChannel]->USART_DR;
			RX_Status[UART_enuUARTChannel] = UART_Busy;
		}
		else
		{

		}
		//*ZeroCpy_u16UARTData = UART[UART_enuUARTChannel]->USART_DR ;
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}

	return Loc_u8State;
}



UART_tenuErrorStatus UART_enuSetCallBackFunc(UART_tenuUARTChannel UART_enuUARTChannel, UART_tenuUARTCallBackType UART_enuUARTCallBackType, void(*Copy_CallBackFunc)(void))
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	if(Copy_CallBackFunc != NULL)
	{
		switch(UART_enuUARTChannel)
		{
		case UART_enuUART1:
			if(UART_enuUARTCallBackType == UART_enuRX)
			{
				UART_CallBackPtrRX[0] = Copy_CallBackFunc;
			}
			else
			{
				UART_CallBackPtrTX[0] = Copy_CallBackFunc;
			}

			break;
		case UART_enuUART2:
			if(UART_enuUARTCallBackType == UART_enuRX)
			{
				UART_CallBackPtrRX[1] = Copy_CallBackFunc;
			}
			else
			{
				UART_CallBackPtrTX[1] = Copy_CallBackFunc;
			}
			break;
		case UART_enuUART6:
			if(UART_enuUARTCallBackType == UART_enuRX)
			{
				UART_CallBackPtrRX[2] = Copy_CallBackFunc;
			}
			else
			{
				UART_CallBackPtrTX[2] = Copy_CallBackFunc;
			}
			break;
		default:
			Loc_u8State = UART_enuNotOK;
			break;
		}
	}
	else
	{
		Loc_u8State = UART_enuNullPtr;
	}

	return Loc_u8State;
}


UART_tenuErrorStatus UART_enuDMAEnable(UART_tenuUARTChannel UART_enuUARTChannel)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	if(UART_enuUARTChannel<UART_enuUARTsNumber)
	{
		SET_BIT(UART[UART_enuUARTChannel]->USART_CR3,DMAT);
		SET_BIT(UART[UART_enuUARTChannel]->USART_CR3,DMAR);
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}


	return Loc_u8State;
}

UART_tenuErrorStatus UART_enuLINEnable(UART_tenuUARTChannel UART_enuUARTChannel)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	if(UART_enuUARTChannel<UART_enuUARTsNumber)
	{
		SET_BIT(UART[UART_enuUARTChannel]->USART_CR2,LINEN);
		SET_BIT(UART[UART_enuUARTChannel]->USART_CR2,LBDIE);
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}


	return Loc_u8State;

}

void USART1_IRQHandler(void)
{
	if((GET_BIT(UART[0]->USART_SR,TXE) == 1) && (TX_Status[0] == UART_Busy))
	{
		if(TX_Index[0] < TX_BufferSize[0])
		{
			TX_Index[0]++;
			UART[0]->USART_DR = *(TX_Buffer[TX_Index[0]]);
		}
		else
		{

			UART_CallBackPtrTX[0]();
			CLR_BIT(UART[0]->USART_CR1,TXEIE);
			TX_Status[0] = UART_Idle;
		}

	}
	else
	{
		//Do nothing
	}

	if((GET_BIT(UART[0]->USART_SR,RXNE) == 1) &&  (RX_Status[0] == UART_Busy))
	{
		if(RX_Index[0] < RX_BufferSize[0])
		{
			RX_Index[0]++;
			*(RX_Buffer[RX_Index[0]]) = UART[0]->USART_DR;
		}
		else
		{
			UART_CallBackPtrRX[0]();
			CLR_BIT(UART[0]->USART_CR1,RXNEIE);
			RX_Status[0] = UART_Idle;
		}

	}
	else
	{
		//Do nothing
	}

}

void USART2_IRQHandler(void)
{
	if((GET_BIT(UART[1]->USART_SR,TXE) == 1) && (TX_Status[1] == UART_Busy))
	{
		if(TX_Index[1] < TX_BufferSize[1])
		{
			TX_Index[1]++;
			UART[1]->USART_DR = *(TX_Buffer[TX_Index[1]]);
		}
		else
		{

			UART_CallBackPtrTX[1]();
			CLR_BIT(UART[1]->USART_CR1,TXEIE);
			TX_Status[1] = UART_Idle;
		}

	}
	else
	{
		//Do nothing
	}

	if((GET_BIT(UART[1]->USART_SR,RXNE) == 1) &&  (RX_Status[1] == UART_Busy))
	{
		if(RX_Index[1] < RX_BufferSize[1])
		{
			RX_Index[1]++;
			*(RX_Buffer[RX_Index[1]]) = UART[1]->USART_DR;
		}
		else
		{
			UART_CallBackPtrRX[1]();
			CLR_BIT(UART[1]->USART_CR1,RXNEIE);
			RX_Status[1] = UART_Idle;
		}

	}
	else
	{
		//Do nothing
	}


}

void USART6_IRQHandler(void)
{

	if((GET_BIT(UART[2]->USART_SR,TXE) == 1) && (TX_Status[2] == UART_Busy))
	{
		if(TX_Index[2] < TX_BufferSize[2])
		{
			TX_Index[2]++;
			UART[2]->USART_DR = *(TX_Buffer[TX_Index[2]]);
		}
		else
		{

			UART_CallBackPtrTX[2]();
			CLR_BIT(UART[2]->USART_CR1,TXEIE);
			TX_Status[2] = UART_Idle;
		}

	}
	else
	{
		//Do nothing
	}

	if((GET_BIT(UART[2]->USART_SR,RXNE) == 1) &&  (RX_Status[2] == UART_Busy))
	{
		if(RX_Index[2] < RX_BufferSize[2])
		{
			RX_Index[2]++;
			*(RX_Buffer[RX_Index[2]]) = UART[2]->USART_DR;
		}
		else
		{
			UART_CallBackPtrRX[2]();
			CLR_BIT(UART[2]->USART_CR1,RXNEIE);
			RX_Status[2] = UART_Idle;
		}

	}
	else
	{
		//Do nothing
	}

}
