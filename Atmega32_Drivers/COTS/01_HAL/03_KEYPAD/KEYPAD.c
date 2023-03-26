/*
 * KEYPAD.c
 *
 * Created: 2/3/2023 11:38:10 AM
 *  Author: HP
 */ 

#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "../../00_MCAL/00_DIO/DIO.h"
#include "KEYPAD.h"
#include "KEYPAD_Cfg.h"
#include "KEYPAD_piv.h"
#include <util/delay.h>




KEYPAD_tenuErrorStatus KEYPAD_enuKeypadRead(u8* Add_pu8_KeyPressed)
{
	KEYPAD_tenuErrorStatus Loc_tenuState = KEYPAD_enuOK;
	u8 Loc_u8Row, Loc_u8Col;
	u8 Loc_u8Value;

	
	DIO_enuSetPin(KEYPAD_Rowpin0);
	DIO_enuSetPin(KEYPAD_Rowpin1);
	DIO_enuSetPin(KEYPAD_Rowpin2);
	DIO_enuSetPin(KEYPAD_Rowpin3);

	DIO_enuSetPin(KEYPAD_Colpin0);
	DIO_enuSetPin(KEYPAD_Colpin1);
	DIO_enuSetPin(KEYPAD_Colpin2);
	DIO_enuSetPin(KEYPAD_Colpin3);
	u8 tarr_rows[KEYPAD_Rows]=  {KEYPAD_Rowpin0,KEYPAD_Rowpin1,KEYPAD_Rowpin2,KEYPAD_Rowpin3};
	u8 tarr_cols[KEYPAD_Cols]=  {KEYPAD_Colpin0,KEYPAD_Colpin1,KEYPAD_Colpin2,KEYPAD_Colpin3};




if(Add_pu8_KeyPressed != NULL)
{
	for(Loc_u8Col=0; Loc_u8Col<KEYPAD_Cols;Loc_u8Col++)
	{
	
		DIO_enuClearPin( tarr_cols[Loc_u8Col]);
			
		for(Loc_u8Row=0; Loc_u8Row<KEYPAD_Rows;Loc_u8Row++)
		{
			DIO_enuGetPin(tarr_rows[Loc_u8Row], &Loc_u8Value);
			if(Loc_u8Value == 0)
			{
				_delay_ms(30);
				DIO_enuGetPin(tarr_rows[Loc_u8Row], &Loc_u8Value);
				if(Loc_u8Value == 0)
				{
					* Add_pu8_KeyPressed = KEYPAD_Buttons[Loc_u8Row][Loc_u8Col];
				}
				
				DIO_enuGetPin(tarr_rows[Loc_u8Row], &Loc_u8Value);
				while(Loc_u8Value == 0)
				{
					DIO_enuGetPin(tarr_rows[Loc_u8Row], &Loc_u8Value);
				}
				break;
			}
		}
		
		DIO_enuSetPin( tarr_cols[Loc_u8Col]);
	}
}
else
{
	 Loc_tenuState = KEYPAD_enuNullPtr;
}

return Loc_tenuState;
}