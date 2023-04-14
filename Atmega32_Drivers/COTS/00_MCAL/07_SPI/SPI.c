/*
 * SPI.c
 *
 * Created: 4/4/2023 3:04:56 PM
 *  Author: HP
 */ 

#include "../../LIB/bit_math.h"
#include "../../LIB/std_defines.h"
#include "SPI.h"
#include "SPI_Cfg.h"
#include "SPI_prv.h"

#define InitCLRMask  0b11000000

static void (*CallBackPtr_SPI)(void);
extern const SPI_tstrCfg SPI_strCfg;


void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
	
	if( CallBackPtr_SPI != NULL)
	{
		CallBackPtr_SPI();
	}
	else
	{
	}
}


SPI_tenuErrorStatus SPI_enuInit(void)
{
	SPI_tenuErrorStatus Loc_u8State = SPI_enuOk;
	SET_BIT(SPCR,SPE);
	SPCR &= InitCLRMask;
	SPCR |= (SPI_strCfg.SPI_enuSPIDataOrder<<DORD);
	//SPCR |= (SPI_strCfg.SPI_enuMasterSlaveSel<<MSTR);
	SPCR |= (SPI_strCfg.SPI_enuClkPolarity<<CPOL);
	SPCR |= (SPI_strCfg.SPI_enuClkPhase<<CPHA);
	if(SPI_strCfg.SPI_enuMasterSlaveSel == SPI_enuSlave)
	{
		CLR_BIT(SPCR,MSTR);
	}
	else
	{
		SET_BIT(SPCR,MSTR);
	}
	switch(SPI_strCfg.SPI_enuClkRatePre)
	{
		case SPI_enuClk_2:
			SET_BIT(SPSR,SPI2X);
			break;
		case SPI_enuClk_4:
			CLR_BIT(SPSR,SPI2X);
			break;
		case SPI_enuClk_8:
			SET_BIT(SPCR,SPR0);
			SET_BIT(SPSR,SPI2X);
			break;
		case SPI_enuClk_16:
			SET_BIT(SPCR,SPR0);
			CLR_BIT(SPSR,SPI2X);
			break;
		case SPI_enuClk_32:
			SET_BIT(SPCR,SPR1);
			SET_BIT(SPSR,SPI2X);
			break;
		case SPI_enuClk_64:
			SET_BIT(SPCR,SPR1);
			CLR_BIT(SPSR,SPI2X);
			break;
		case SPI_enuClk_128:
			SET_BIT(SPCR,SPR0);
			SET_BIT(SPCR,SPR1);
			CLR_BIT(SPSR,SPI2X);
			break;
		
	}
	
	return Loc_u8State;
}


SPI_tenuErrorStatus  SPI_enuSendAsyncByte(u8  SPI_u8SendByteValue)
{
	SPI_tenuErrorStatus Loc_u8State = SPI_enuOk;
	SET_BIT(SPCR,SPIE);
	ASSIGN_REG(SPDR,SPI_u8SendByteValue);
	return Loc_u8State;
	 
}
 
 
SPI_tenuErrorStatus  SPI_enuTranseiveSyncByte(u8  SPI_u8SendByteValue, u8 * SPI_u8RecByteValue)
{
	SPI_tenuErrorStatus Loc_u8State = SPI_enuOk;
	u16 Loc_u16Count = 0;
	ASSIGN_REG(SPDR,SPI_u8SendByteValue);
	while((!GET_BIT(SPSR,SPIF)) && (Loc_u16Count < TIMEOUT))
	{
		Loc_u16Count++;
	}
	
	if(SPI_u8RecByteValue != NULL)
	{
		* SPI_u8RecByteValue = SPDR;
	}
	else
	{
		Loc_u8State = SPI_NullPtr;
	}
	return Loc_u8State;	  
	  
}
  
  


SPI_tenuErrorStatus  SPI_enuSetCallBack( void(*Cpy_CallBackPtr)(void))
{
	SPI_tenuErrorStatus Loc_u8State = SPI_enuOk;
	if(Cpy_CallBackPtr != NULL)
	{
		CallBackPtr_SPI = Cpy_CallBackPtr;
		
	}
	else
	{
		Loc_u8State = SPI_NullPtr;
	}
	
	return Loc_u8State; 
	 
}