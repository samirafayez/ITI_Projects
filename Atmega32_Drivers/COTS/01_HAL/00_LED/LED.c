#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "../../00_MCAL/00_DIO/DIO.h"

#include "LED.h"
#include "LED_Cfg.h"
#include "LED_piv.h"





LED_tenuErrorStatus LED_enuLEDon(LED_tenuPins Cpy_u8PinNumber){

	
		if(LED_strPinCfg[Cpy_u8PinNumber].LED_ActiveStatus == LED_ACTIVE_HIGH)
		{
			DIO_enuSetPin(Cpy_u8PinNumber);
		}
		else
		{
			DIO_enuClearPin(Cpy_u8PinNumber);
		}
	

	return LED_enuOK;
}
LED_tenuErrorStatus LED_enuLEDoff(LED_tenuPins Cpy_u8PinNumber)
{


	if(LED_strPinCfg[Cpy_u8PinNumber].LED_ActiveStatus == LED_ACTIVE_HIGH)
	{
		DIO_enuClearPin(Cpy_u8PinNumber);
	}
	else
	{
		DIO_enuSetPin(Cpy_u8PinNumber);
	}


return LED_enuOK;
}	


LED_tenuErrorStatus LED_enuLEDToggle(LED_tenuPins Cpy_u8PinNumber)
{
	LED_tenuErrorStatus Loc_u8State = LED_enuOK;
	
	DIO_enuTogglePin(Cpy_u8PinNumber);
	
	return Loc_u8State;
	
}