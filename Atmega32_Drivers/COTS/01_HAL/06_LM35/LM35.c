/*
 * LM35.c
 *
 * Created: 2/17/2023 5:01:07 AM
 *  Author: HP
 */ 

#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "../../00_MCAL/03_ADC/ADC.h"
#include "LM35.h"
#include "LM35_prv.h"
#include "LM35_Cfg.h"



LM35_tenuErrorStatus LM35_enuReadValue(ADC_tenuChannelNumber Cpy_u8ChannelNumber, u16* Add_pu8_PinValue)
{
	LM35_tenuErrorStatus Loc_u8State = LM35_enuOK;
	
	if((Cpy_u8ChannelNumber>=0) && (Cpy_u8ChannelNumber<8))
	{
		ADC_enuSelectChannel(Cpy_u8ChannelNumber);
	}
	else
	{
		Loc_u8State = LM35_enuNotOK;
	}
	
	if(Add_pu8_PinValue != NULL)
	{
		ADC_enuSynchGetADCValue( Add_pu8_PinValue);
		//(*Add_pu8_PinValue) *= (5/1024);
		(*Add_pu8_PinValue) *= 500;
		(*Add_pu8_PinValue) /= 1024;

	
	}
	else
	{
		Loc_u8State = LM35_enuNullPtr;
	}
	
	
	return Loc_u8State;
	
}