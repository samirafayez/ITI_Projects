/*
 * I2C.c
 *
 * Created: 4/16/2023 8:27:08 PM
 *  Author: HP
 */ 


#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "I2C.h"
#include "I2C_Cfg.h"
#include "I2C_prv.h"


#define I2C_SlaveCheck_MASK      0b01111000
#define I2C_PrescalerCLR_MASK    0b11111100


extern const I2C_tstrCFG_t I2C_strCFG;

I2C_tenuErrorStatus I2C_enuInit(void)
{
	I2C_tenuErrorStatus Loc_u8State = I2C_enuOk;
	//Bit Rate
	ASSIGN_REG(TWBR, I2C_strCFG.I2C_BitRate);
	//Setting Prescaler
	if(I2C_strCFG.I2C_Prescaler < 4)
	{
		TWSR &= I2C_PrescalerCLR_MASK;
		TWSR |= I2C_strCFG.I2C_Prescaler;
	}
	else
	{
		Loc_u8State = I2C_enuNotOk;
	}
	//Setting Slave Address and General Call Recognition Enable
	if((I2C_strCFG.I2C_SlaveAddress != 0) && ((I2C_strCFG.I2C_SlaveAddress & I2C_SlaveCheck_MASK) != I2C_SlaveCheck_MASK))
	{
		TWAR &= 0;
		TWAR |= (I2C_strCFG.I2C_SlaveAddress << 1) | (I2C_strCFG.GeneralCallRecognitionEN);
	}
	else
	{
		Loc_u8State = I2C_enuNotOk;
	}
	if(I2C_strCFG.I2C_InterruptEN == I2C_enuEnabled)
	{
		SET_BIT(TWCR, TWINT);	
	}
	else if(I2C_strCFG.I2C_InterruptEN == I2C_enuDisabled)
	{
		CLR_BIT(TWCR, TWINT);
	}
	else
	{
		Loc_u8State = I2C_enuNotOk;		
	}
	if(I2C_strCFG.I2C_AcknowledgeEN == I2C_enuEnabled)
	{
		SET_BIT(TWCR, TWEA);
	}
	else if(I2C_strCFG.I2C_AcknowledgeEN == I2C_enuDisabled)
	{
		CLR_BIT(TWCR, TWEA);
	}
	else
	{
		Loc_u8State = I2C_enuNotOk;
	}
	//Enabling I2C
	SET_BIT(TWCR, TWEN);
	
	
	return Loc_u8State;
}



I2C_tenuErrorStatus I2C_enuSendStartCondition(void)
{
	I2C_tenuErrorStatus Loc_u8State = I2C_enuOk;
	SET_BIT(TWCR, TWSTA);
	SET_BIT(TWCR, TWINT);
	while(!GET_BIT(TWCR, TWINT));
	//check on message ID
	if((TWSR & 0xF8) != 0x08)
	{
		Loc_u8State = I2C_enuNotOk;
	}
	CLR_BIT(TWCR, TWSTA);
	
	return Loc_u8State;
}



I2C_tenuErrorStatus I2C_enuSendRepeatedStart(void)
{
	I2C_tenuErrorStatus Loc_u8State = I2C_enuOk;
	SET_BIT(TWCR, TWSTA);
	SET_BIT(TWCR, TWINT);
	while(!GET_BIT(TWCR, TWINT));
	//check on message ID
	if((TWSR & 0xF8) != 0x10)
	{
		Loc_u8State = I2C_enuNotOk;
	}
	CLR_BIT(TWCR, TWSTA);
	
	return Loc_u8State;
	
}



I2C_tenuErrorStatus I2C_enuSlaveAddressPlusWrite(u8 Cpy_u8SlaveAddress)
{
	I2C_tenuErrorStatus Loc_u8State = I2C_enuOk;
	if((Cpy_u8SlaveAddress != 0) && ((Cpy_u8SlaveAddress & I2C_SlaveCheck_MASK) != I2C_SlaveCheck_MASK))
	{
		
		ASSIGN_REG(TWDR, (Cpy_u8SlaveAddress << 1)); //slave + write
		SET_BIT(TWCR, TWINT);
		while(!GET_BIT(TWCR, TWINT));
		//wait for Acknowledge
		if((I2C_strCFG.I2C_AcknowledgeEN == I2C_enuEnabled) && ((TWSR & 0xF8) != 0x18))
		{
			Loc_u8State = I2C_enuNotOk;
		}
		else if ((I2C_strCFG.I2C_AcknowledgeEN == I2C_enuDisabled) && (TWSR & 0xF8) != 0x20)
		{
			Loc_u8State = I2C_enuNotOk;
		}
		else
		{
			//Do nothing
		}
	}
	else
	{
		Loc_u8State = I2C_enuNotOk;
	}
		return Loc_u8State;
}


I2C_tenuErrorStatus I2C_enuSlaveAddressPlusRead(u8 Cpy_u8SlaveAddress)
{
	I2C_tenuErrorStatus Loc_u8State = I2C_enuOk;
	if((Cpy_u8SlaveAddress != 0) && ((Cpy_u8SlaveAddress & I2C_SlaveCheck_MASK) != I2C_SlaveCheck_MASK))
	{
		
		ASSIGN_REG(TWDR, (Cpy_u8SlaveAddress << 1)); //slave + read
		TWDR |= 1;
		SET_BIT(TWCR, TWINT);
		while(!GET_BIT(TWCR, TWINT));
		//wait for Acknowledge
		if((I2C_strCFG.I2C_AcknowledgeEN == I2C_enuEnabled) && ((TWSR & 0xF8) != 0x40))
		{
			Loc_u8State = I2C_enuNotOk;
		}
		else if ((I2C_strCFG.I2C_AcknowledgeEN == I2C_enuDisabled) && (TWSR & 0xF8) != 0x48)
		{
			Loc_u8State = I2C_enuNotOk;
		}
		else
		{
			//Do nothing
		}
	}
	else
	{
		Loc_u8State = I2C_enuNotOk;
	}
		return Loc_u8State;	
}


I2C_tenuErrorStatus I2C_enuWriteData(u8 Cpy_u8Data)
{
	I2C_tenuErrorStatus Loc_u8State = I2C_enuOk;
	
	ASSIGN_REG(TWDR, Cpy_u8Data);
	SET_BIT(TWCR, TWINT);
	while(!GET_BIT(TWCR, TWINT));
	//wait for Acknowledge
	if((I2C_strCFG.I2C_AcknowledgeEN == I2C_enuEnabled) && ((TWSR & 0xF8) != 0x28))
	{
		Loc_u8State = I2C_enuNotOk;
	}
	else if ((I2C_strCFG.I2C_AcknowledgeEN == I2C_enuDisabled) && (TWSR & 0xF8) != 0x30)
	{
		Loc_u8State = I2C_enuNotOk;
	}
	else
	{
		//Do nothing
	}
	
	
	return Loc_u8State;
}



I2C_tenuErrorStatus I2C_enuReceiveData(u8 * Add_pu8Data)
{
	I2C_tenuErrorStatus	Loc_u8State = I2C_enuOk;
	SET_BIT(TWCR, TWINT);
	while(!GET_BIT(TWCR, TWINT));
	//wait for Acknowledge
	if((I2C_strCFG.I2C_AcknowledgeEN == I2C_enuEnabled) && ((TWSR & 0xF8) != 0x50))
	{
		Loc_u8State = I2C_enuNotOk;
	}
	else if ((I2C_strCFG.I2C_AcknowledgeEN == I2C_enuDisabled) && (TWSR & 0xF8) != 0x58)
	{
		Loc_u8State = I2C_enuNotOk;
	}
	else
	{
		* Add_pu8Data = TWDR;
	}
	return Loc_u8State;
}



I2C_tenuErrorStatus I2C_enuSendStopCondition(void)
{
	I2C_tenuErrorStatus Loc_u8State = I2C_enuOk;
	SET_BIT(TWCR, TWSTO);
	SET_BIT(TWCR, TWINT);
	
	return Loc_u8State;
}