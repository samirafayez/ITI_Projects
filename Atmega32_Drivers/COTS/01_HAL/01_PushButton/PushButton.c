
#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "../../00_MCAL/00_DIO/DIO.h"
#include "PushButton.h"
#include "PushButton_Cfg.h"
#include "PushButton_piv.h"
#include <util/delay.h>





PushButton_tenuErrorStatus PushButton_enuPushButton_Read(DIO_tenuPins Cpy_u8PinNumber, u8* Add_pu8_PinValue)
{
	PushButton_tenuErrorStatus state=PushButton_enuOK;
	u8 i;

if(PushButton_strPinCfg[Cpy_u8PinNumber].PushButton_InputStatus == PushButton_PULL_UP)
{
	
DIO_enuGetPin(Cpy_u8PinNumber, Add_pu8_PinValue);
if (*Add_pu8_PinValue==0)
{
	for(i=0;i<10;i++)
	{
		_delay_ms(20);
		DIO_enuGetPin(Cpy_u8PinNumber, Add_pu8_PinValue);
		
	}
	
}
	
	
}
else if(PushButton_strPinCfg[Cpy_u8PinNumber].PushButton_InputStatus == PushButton_PULL_DOWN)
{
if (Add_pu8_PinValue==1)
{
	for(i=0;i<10;i++)
	{
		_delay_ms(20);
		DIO_enuGetPin(Cpy_u8PinNumber, Add_pu8_PinValue);
		
	}
}
}
else
{
	state=PushButton_enuNotOK;
}


return state;
}