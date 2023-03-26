/*
 * LCD.c
 *
 * Created: 2/11/2023 4:32:53 AM
 *  Author: HP
 */ 

#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "../../00_MCAL/00_DIO/DIO.h"
#include "LCD.h"
#include "LCD_prv.h"
#include "LCD_Cfg.h"
#include <util/delay.h> 
#include <string.h>



LCD_enuErrorStatus LCD_vidInit(void)
{
	LCD_enuErrorStatus Loc_u8State = LCD_enuOk;
	//DIO_enuInit();
	_delay_ms(30);
	/*Set Function*/
	DIO_enuClearPin(RS);
	DIO_enuClearPin(RW);
	DIO_enuClearPin(LCD_PinD7);
	DIO_enuClearPin(LCD_PinD6);
	DIO_enuSetPin(LCD_PinD5);
	DIO_enuClearPin(LCD_PinD4);
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	//_delay_ms(5);
	
	/*DIO_enuClearPin(LCD_PinD7);
	DIO_enuClearPin(LCD_PinD6);
	DIO_enuSetPin(LCD_PinD5);
	DIO_enuClearPin(LCD_PinD4);*/
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	//_delay_ms(5);
	
	/*DIO_enuClearPin(LCD_PinD7);
	DIO_enuClearPin(LCD_PinD6);
	DIO_enuSetPin(LCD_PinD5);
	DIO_enuClearPin(LCD_PinD4);*/
	DIO_enuSetPin(LCD_PinD7);
	DIO_enuSetPin(LCD_PinD6);
	DIO_enuClearPin(LCD_PinD5);
	DIO_enuClearPin(LCD_PinD4);
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	_delay_ms(5);
	
	/*Display ON/OFF Control*/
	DIO_enuClearPin(LCD_PinD7);
	DIO_enuClearPin(LCD_PinD6);
	DIO_enuClearPin(LCD_PinD5);
	DIO_enuClearPin(LCD_PinD4);
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	
	DIO_enuSetPin(LCD_PinD7);
	//DIO_enuClearPin(LCD_PinD6);
	DIO_enuSetPin(LCD_PinD6);
	DIO_enuClearPin(LCD_PinD5);
	DIO_enuClearPin(LCD_PinD4);
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	_delay_ms(5);
	
	/* Display Clear*/
	DIO_enuClearPin(LCD_PinD7);
	DIO_enuClearPin(LCD_PinD6);
	DIO_enuClearPin(LCD_PinD5);
	DIO_enuClearPin(LCD_PinD4);
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	
	DIO_enuClearPin(LCD_PinD7);
	DIO_enuClearPin(LCD_PinD6);
	DIO_enuClearPin(LCD_PinD5);
	DIO_enuSetPin(LCD_PinD4);
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	_delay_ms(5);
	
	/*Entry Mode Set*/
	DIO_enuClearPin(LCD_PinD7);
	DIO_enuClearPin(LCD_PinD6);
	DIO_enuClearPin(LCD_PinD5);
	DIO_enuClearPin(LCD_PinD4);
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	
	DIO_enuClearPin(LCD_PinD7);
	DIO_enuSetPin(LCD_PinD6);
	DIO_enuSetPin(LCD_PinD5);
	DIO_enuClearPin(LCD_PinD4);
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	_delay_ms(5);
	
	return Loc_u8State;
}


LCD_enuErrorStatus LCD_enuSendData (u8 Copy_u8Data)
{
	LCD_enuErrorStatus Loc_u8State = LCD_enuOk;
	DIO_enuSetPin(RS);
	DIO_enuClearPin(RW);
	
	DIO_enuSetPinValue(LCD_PinD7, GET_BIT(Copy_u8Data,7));
	DIO_enuSetPinValue(LCD_PinD6, GET_BIT(Copy_u8Data,6));
	DIO_enuSetPinValue(LCD_PinD5, GET_BIT(Copy_u8Data,5));
	DIO_enuSetPinValue(LCD_PinD4, GET_BIT(Copy_u8Data,4));
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	
	DIO_enuSetPinValue(LCD_PinD7, GET_BIT(Copy_u8Data,3));
	DIO_enuSetPinValue(LCD_PinD6, GET_BIT(Copy_u8Data,2));
	DIO_enuSetPinValue(LCD_PinD5, GET_BIT(Copy_u8Data,1));
	DIO_enuSetPinValue(LCD_PinD4, GET_BIT(Copy_u8Data,0));
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	_delay_ms(2);
	
	return Loc_u8State;
}


LCD_enuErrorStatus LCD_enuSendCommand (u8 Copy_u8Command)
{
	LCD_enuErrorStatus Loc_u8State = LCD_enuOk;
	DIO_enuClearPin(RS);
	DIO_enuClearPin(RW);
	
	DIO_enuSetPinValue(LCD_PinD7, GET_BIT(Copy_u8Command,7));
	DIO_enuSetPinValue(LCD_PinD6, GET_BIT(Copy_u8Command,6));
	DIO_enuSetPinValue(LCD_PinD5, GET_BIT(Copy_u8Command,5));
	DIO_enuSetPinValue(LCD_PinD4, GET_BIT(Copy_u8Command,4));
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	
	DIO_enuSetPinValue(LCD_PinD7, GET_BIT(Copy_u8Command,3));
	DIO_enuSetPinValue(LCD_PinD6, GET_BIT(Copy_u8Command,2));
	DIO_enuSetPinValue(LCD_PinD5, GET_BIT(Copy_u8Command,1));
	DIO_enuSetPinValue(LCD_PinD4, GET_BIT(Copy_u8Command,0));
	
	DIO_enuSetPin(EN);
	_delay_ms(2);
	DIO_enuClearPin(EN);
	_delay_ms(2);

	
	return Loc_u8State;
}


LCD_enuErrorStatus LCD_enuGotoXY (u8 Copy_u8XPos, u8 Copy_u8YPos) //x is the col and y is the row
{
	LCD_enuErrorStatus Loc_u8State = LCD_enuOk;
	u8 Loc_u8Address = 0;
	if((Copy_u8YPos < 2) && (Copy_u8XPos < 16))
	{
		Loc_u8Address = (Copy_u8YPos * 0x40) + Copy_u8XPos;
		SET_BIT(Loc_u8Address,7);
		LCD_enuSendCommand(Loc_u8Address);
	}
	else
	{
		Loc_u8State = LCD_enuNotOk;
	}
	return Loc_u8State;
}


LCD_enuErrorStatus LCD_enuWriteSpecialPattern (u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	LCD_enuErrorStatus Loc_u8State = LCD_enuOk;
	u8 Loc_u8Iter;
	u8 Loc_u8Address = 0;
	
	if(Copy_u8BlockNum<8)
	{
		Loc_u8Address = Copy_u8BlockNum*8;
		SET_BIT(Loc_u8Address,6);
		LCD_enuSendCommand(Loc_u8Address);
		for(Loc_u8Iter =0; Loc_u8Iter<8; Loc_u8Iter++)
		{
			LCD_enuSendData(Add_pu8Pattern[Loc_u8Iter]);
		}
		LCD_enuSendCommand(0x02); //Return to DDRAM
		LCD_enuGotoXY(Copy_u8XPos,Copy_u8YPos);
		LCD_enuSendData(Copy_u8BlockNum);
	}
	else
	{
		Loc_u8State = LCD_enuNotOk;
	}
	return Loc_u8State;
}


LCD_enuErrorStatus LCD_enuWriteString (char* Add_pchString)
{
	LCD_enuErrorStatus Loc_u8State = LCD_enuOk;
	u8 Loc_u8Index = 0;
	while(Add_pchString[Loc_u8Index] != '\0')
	{
		LCD_enuSendData(Add_pchString[Loc_u8Index]);
		Loc_u8Index++;
	}	
	return Loc_u8State;
}


LCD_enuErrorStatus LCD_enuWriteNumber (u16 Copy_u16Number)
{
	LCD_enuErrorStatus Loc_u8State = LCD_enuOk;
	u16 Loc_u16CopyNumber = Copy_u16Number;
	u8 Loc_u8Mod = 0;
	u16 Loc_u8Reversed = 0;
	u8 Loc_u8ArraySize =0;
	
	if(Copy_u16Number == 0)
	{
		LCD_enuSendData(48);
	}
	else
	{
	while (Loc_u16CopyNumber != 0) {
		Loc_u8Mod = Loc_u16CopyNumber % 10;
		Loc_u8Reversed = Loc_u8Reversed * 10 + Loc_u8Mod;
		Loc_u8ArraySize++;
		Loc_u16CopyNumber /= 10;
	}
	while(Loc_u8ArraySize--)
	{
		Loc_u8Mod = Loc_u8Reversed % 10;
		Loc_u8Mod += 48;  //Adding the 0b00110000 on the number
		LCD_enuSendData(Loc_u8Mod);
		Loc_u8Reversed/=10;
	}
	}
	return Loc_u8State;
}



LCD_enuErrorStatus LCD_enuClearScreen(void)
{
	LCD_enuErrorStatus Loc_u8State = LCD_enuOk;
	
	LCD_enuSendCommand(0x01);
	return Loc_u8State;
}



LCD_enuErrorStatus LCD_enuReturntohome(void)
{
	LCD_enuErrorStatus Loc_u8State = LCD_enuOk;
	LCD_enuSendCommand(0x02);
	return Loc_u8State;
}