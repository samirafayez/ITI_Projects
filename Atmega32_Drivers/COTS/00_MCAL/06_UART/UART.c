/*
 * UART.c
 *
 * Created: 3/18/2023 8:50:55 AM
 *  Author: HP
 */ 


#include <math.h>
#include "../../LIB/bit_math.h"
#include "../../LIB/std_defines.h"
#include "UART.h"
#include "UART_prv.h"
#include "UART_Cfg.h"
#define F_CPU 1000000UL

extern const UART_tstrCfg UART_strCfg;

static void(*UART_CallBackPtr[3])(void) = {NULL};
	
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	if( UART_CallBackPtr[0] != NULL)
	{
		UART_CallBackPtr[0]();
	}
	else
	{
	}
}

void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
	if( UART_CallBackPtr[1] != NULL)
	{
		UART_CallBackPtr[1]();
	}
	else
	{
	}	
}

void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
	if( UART_CallBackPtr[2] != NULL)
	{
		UART_CallBackPtr[2]();
	}
	else
	{
	}	
}

UART_tenuErrorStatus UART_enuInit(void)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	f64 Loc_BaudRate = 0.0;
	u32 Loc_ResBaudRate = 0;
	
	/*URSEL must be one when writing the UCSRC*/
	SET_BIT(UCSRC,URSEL);
	
	if(UART_strCfg.UART_Mode == UART_enuAsynchronous)
	{
		CLR_BIT(UCSRC,UMSEL);
	}
	else if(UART_strCfg.UART_Mode == UART_enuSynchronous)
	{
		SET_BIT(UCSRC,UMSEL);
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}
	
	switch(UART_strCfg.UART_CharacterNumber)
	{
		case UART_enu5Characters:
			CLR_BIT(UCSRC,UCSZ0);
			CLR_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRB,UCSZ2);
			break;
		case UART_enu6Characters:
			SET_BIT(UCSRC,UCSZ0);
			CLR_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRB,UCSZ2);
			break;
		case UART_enu7Characters:
			CLR_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRB,UCSZ2);
			break;
		case UART_enu8Characters:
			SET_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRB,UCSZ2);
			break;
		case UART_enu9Characters:
			SET_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			SET_BIT(UCSRB,UCSZ2);
			break;
		default:
			Loc_u8State = UART_enuNotOK;
			break;
	}
	
	if((UART_strCfg.UART_ParityMode == UART_enuDisabled) || (UART_strCfg.UART_ParityMode == UART_enuEvenParity) || (UART_strCfg.UART_ParityMode == UART_enuOddParity))
	{
		UCSRC &= UART_ParityMode_CLRMask;
		UCSRC |= (UART_strCfg.UART_ParityMode<<UPM0);
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}
	
	if(UART_strCfg.UART_ClkPolarity == UART_TxDataChangedPositiveEdge)
	{
		CLR_BIT(UCSRC,UCPOL);
	}
	else if(UART_strCfg.UART_ClkPolarity == UART_TxDataChangedNegativeEdge)
	{
		SET_BIT(UCSRC,UCPOL);
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}
		
	if(UART_strCfg.UART_StopBitNumber == 1)
	{
		CLR_BIT(UCSRC,USBS);
	}
	else if(UART_strCfg.UART_StopBitNumber == 2)
	{
		SET_BIT(UCSRC,USBS);
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}
	/*URSEL must be zero when writing the UBBRH*/
	CLR_BIT(UCSRC,URSEL);
	if((UART_strCfg.UART_Mode == UART_enuAsynchronous) && (UART_strCfg.UART_DoubleSpeed == UART_enu2SpeedDisabled))
	{
		Loc_BaudRate = (F_CPU/(f64)(16*UART_strCfg.UART_BaudRate))-1;
		Loc_BaudRate = ceil(Loc_BaudRate);
		Loc_ResBaudRate = (u32)Loc_BaudRate;
	}
	else if((UART_strCfg.UART_Mode == UART_enuAsynchronous) && (UART_strCfg.UART_DoubleSpeed == UART_enu2SpeedEnabled))
	{
		Loc_BaudRate = (F_CPU/(f64)(8*UART_strCfg.UART_BaudRate))-1;
		Loc_BaudRate = ceil(Loc_BaudRate);
		Loc_ResBaudRate = (u32)Loc_BaudRate;		
	}
	else if(UART_strCfg.UART_Mode == UART_enuSynchronous)
	{
		Loc_BaudRate = (F_CPU/(f64)(2*UART_strCfg.UART_BaudRate))-1;
		Loc_BaudRate = ceil(Loc_BaudRate);
		Loc_ResBaudRate = (u32)Loc_BaudRate;
	}
	else
	{
		Loc_u8State = UART_enuNotOK;
	}
	
	ASSIGN_REG(UBRRL,Loc_ResBaudRate);
	ASSIGN_REG(UBRRH,(Loc_ResBaudRate>>8) & UART_UBRRH_HighNibbleCLRMask);
	
	/*Enabling Sending and Receiving*/
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	
	return Loc_u8State;
}



UART_tenuErrorStatus UART_enuSendAsyncByte(u16 UART_u16UARTByteValue)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	SET_BIT(UCSRB,TXCIE);	
	if (UART_strCfg.UART_CharacterNumber == UART_enu9Characters)
	{
		UCSRB |= ((UART_u16UARTByteValue>>8)&1);
		ASSIGN_REG(UDR,UART_u16UARTByteValue);
	}
	else
	{
		ASSIGN_REG(UDR,UART_u16UARTByteValue);
	}
		
	return Loc_u8State;
}


UART_tenuErrorStatus UART_enuSendSyncByte(u16 UART_u16UARTByteValue)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	if (UART_strCfg.UART_CharacterNumber == UART_enu9Characters)
	{
		UCSRB |= ((UART_u16UARTByteValue>>8)&1);
		ASSIGN_REG(UDR,UART_u16UARTByteValue);
	}
	else
	{
		ASSIGN_REG(UDR,UART_u16UARTByteValue);
	}
	while(!GET_BIT(UCSRA,TXC));
	return Loc_u8State;
}


UART_tenuErrorStatus UART_enuRecieveAsyncByte(u16 * UART_u16UARTByteValue)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	SET_BIT(UCSRB,RXCIE);
	if(UART_u16UARTByteValue != NULL)
	{
		if (UART_strCfg.UART_CharacterNumber == UART_enu9Characters)
		{
			* UART_u16UARTByteValue = ((UCSRB&(1<<1))<<8);
			* UART_u16UARTByteValue |= UDR;
		}
		else
		{
			* UART_u16UARTByteValue = UDR;
		}
	}
	else
	{
		Loc_u8State = UART_enuNullPtr;
	}
	while(!GET_BIT(UCSRA,RXC));
	return Loc_u8State;	
	
}


UART_tenuErrorStatus UART_enuRecieveSyncByte(u16 * UART_u16UARTByteValue)
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	SET_BIT(UCSRB,RXCIE);
	if(UART_u16UARTByteValue != NULL)
	{
		if (UART_strCfg.UART_CharacterNumber == UART_enu9Characters)
		{
			* UART_u16UARTByteValue = ((UCSRB&(1<<1))<<8);
			* UART_u16UARTByteValue |= UDR;
		}
		else
		{
			* UART_u16UARTByteValue = UDR;
		}
	}
	else
	{
		Loc_u8State = UART_enuNullPtr;
	}	
	return Loc_u8State;
}


UART_tenuErrorStatus UART_enuSetCallBack(UART_tenuINTSource Cpy_enuINTSource, void(*Cpy_CallBackPtr)(void))
{
	UART_tenuErrorStatus Loc_u8State = UART_enuOK;
	if(Cpy_CallBackPtr != NULL)
	{
		
		switch(Cpy_enuINTSource)
		{
			case UART_RXComplete:
				UART_CallBackPtr[0] = Cpy_CallBackPtr;
				break;
			case UART_DataRegisterEMPTY:
				UART_CallBackPtr[1] = Cpy_CallBackPtr;
				break;
			case UART_TXComplete:
				UART_CallBackPtr[2] = Cpy_CallBackPtr;
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