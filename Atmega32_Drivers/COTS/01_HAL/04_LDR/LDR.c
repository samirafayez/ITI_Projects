/*
 * LDR.c
 *
 * Created: 2/10/2023 2:49:33 AM
 *  Author: HP
 */ 


#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "../../00_MCAL/03_ADC/ADC.h"
#include "LDR.h"
#include "LDR_prv.h"
#include "LDR_Cfg.h"



LDR_tenuErrorStatus LDR_enuReadValue(ADC_tenuChannelNumber Cpy_u8ChannelNumber, u16* Add_pu8_PinValue)
{
	LDR_tenuErrorStatus Loc_u8State = LDR_enuOK;
	
	if((Cpy_u8ChannelNumber>=0) && (Cpy_u8ChannelNumber<8))
	{
		ADC_enuSelectChannel(Cpy_u8ChannelNumber);
	}
	else
	{
		Loc_u8State = LDR_enuNotOK;
	}
	
	if(Add_pu8_PinValue != NULL)
	{
		ADC_enuSynchGetADCValue( Add_pu8_PinValue);
	}
	else
	{
		Loc_u8State = LDR_enuNullPtr;
	}
	return Loc_u8State;
}