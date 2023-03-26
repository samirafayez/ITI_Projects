/*
 * SSEG.c
 *
 * Created: 1/20/2023 2:47:41 PM
 *  Author: HP
 */ 

#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "../../00_MCAL/00_DIO/DIO.h"
#include "SSEG.h"
#include "SSEG_Cfg.h"
#include "SSEG_piv.h"




SSEG_tenuErrorStatus SSEG_enuNumberShow(u8 SSEG_u8Port, u8 SSEG_u8Index)
{
u8 i;
u8 Loc_u8PinNumber =0;
u8 Loc_u8PinValue =0;
Loc_u8PinNumber = SSEG_u8Port *8;

/*for(i=Loc_u8PinNumber;i<(Loc_u8PinNumber+8);i++)
{
	
if(SSEG_strPinCfg[i].SSEG_ActiveStatus == SSEG_ACTIVE_HIGH)
{
	Loc_u8PinValue |= (SSEG_LookupTable[SSEG_u8Index]<<i) ;
}
else
{
	Loc_u8PinValue ^= (SSEG_LookupTable[SSEG_u8Index]<<i) ;
	
}

}*/
DIO_enuSetValue(Loc_u8PinNumber,SSEG_LookupTable[SSEG_u8Index]);
return SSEG_enuOK;
}

SSEG_tenuErrorStatus SSEG_enuSSEGoff(u8 SSEG_u8Port)
{
	u8 i;
	u8 Loc_u8PinNumber =0;
	u8 Loc_u8PinValue =0;
	Loc_u8PinNumber = SSEG_u8Port *8;
	
	/*for(i=Loc_u8PinNumber;i<(Loc_u8PinNumber+8);i++)
	{
		
	if(SSEG_strPinCfg[i].SSEG_ActiveStatus == SSEG_ACTIVE_HIGH)
	{
		Loc_u8PinValue |= CLR_BIT(Loc_u8PinValue,i) ;
	}
	else
	{
		Loc_u8PinValue |= SET_BIT(Loc_u8PinValue,i) ;
	}
	
	}*/
	DIO_enuSetValue(Loc_u8PinNumber,Loc_u8PinValue);
	return SSEG_enuOK;
}
