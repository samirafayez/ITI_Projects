/*
 * LCD.c
 *
 *  Created on: Mar 28, 2023
 *      Author: HP
 */


#include "std_defines.h"
#include "bit_math.h"
#include "02_LCD/LCD.h"
#include "02_LCD/LCD_prv.h"
#include "02_LCD/LCD_Cfg.h"
#include "01_GPIO/GPIO.h"
#include "00_Scheduler/Scheduler.h"


#define LCD_FunctionSet 0b00110000
#define LCD_DisplayControl 0b00001000
#define LCD_ClearScreenMASK 0b00000001
#define LCD_EntryModeSetMASK 0b00000110

typedef enum
{
	Lcd_enuStart = 0,
	Lcd_enuFunctionSet,
	Lcd_enuDisplayControl,
	Lcd_enuClear,
	Lcd_enuEntryMode,
	Lcd_enuDone

}Lcd_tenuInitState;


typedef enum
{
	Lcd_enuNoRequest = 0,
	Lcd_enuWritingProcess,
	Lcd_enuSendingCommand

}Lcd_tenuRequest;


typedef enum
{
	Lcd_enuWriteData=0,
	Lcd_enuWriteNumber,
	Lcd_enuWriteString,

}Lcd_tenuWriteProcess;

typedef enum{

	Lcd_enuGotoXY=0,
	Lcd_enuClearScreen,
	Lcd_enuSendCommand_Default

}Lcd_tenuSendCommand;


extern const LCD_tstrCfg LCD_strCfg;
static volatile Lcd_tenuInitState LCD_enuInitState = Lcd_enuStart;
static volatile Lcd_tenuRequest LCD_enuRequest = Lcd_enuNoRequest;
static volatile Lcd_tenuWriteProcess Lcd_enuWriteProcess = Lcd_enuWriteData;
static volatile Lcd_tenuSendCommand Lcd_enuSendCommand = Lcd_enuGotoXY;
static volatile u8 LCD_u8Command;
static volatile u8 LCD_u8Data;
static volatile u16 LCD_u16Number;
static volatile u8 LCD_u8ArraySize;
static volatile u8 LCD_u8Reversed;
static volatile u8 LCD_u8_X;
static volatile u8 LCD_u8_Y;
static volatile char * LCD_StringValue;
static volatile u8 LCD_u8Index;
//static volatile u8 * LCD_Pattern;
//static volatile u8  LCD_BlockNumber;




static void Lcd_vidPinInit(void);
void Lcd_vidPinInit(void)
{
	u8 Loc_u8IterVar;
	GPIOcgf_t Loc_LCDGPIOcgf;
	Loc_LCDGPIOcgf.MODE = GPIO_MODE_PP;
	Loc_LCDGPIOcgf.PORT = LCD_strCfg.LCD_tstrPins.LCD_RSPin.LCD_Port;
	Loc_LCDGPIOcgf.PIN = LCD_strCfg.LCD_tstrPins.LCD_RSPin.LCD_Pin;
	Loc_LCDGPIOcgf.SPEED = GPIO_SPEED_HIGH;
	GPIO_Init(&Loc_LCDGPIOcgf);
	Loc_LCDGPIOcgf.MODE = GPIO_MODE_PP;
	Loc_LCDGPIOcgf.PORT = LCD_strCfg.LCD_tstrPins.LCD_RWPin.LCD_Port;
	Loc_LCDGPIOcgf.PIN = LCD_strCfg.LCD_tstrPins.LCD_RWPin.LCD_Pin;
	Loc_LCDGPIOcgf.SPEED = GPIO_SPEED_HIGH;
	GPIO_Init(&Loc_LCDGPIOcgf);
	Loc_LCDGPIOcgf.MODE = GPIO_MODE_PP;
	Loc_LCDGPIOcgf.PORT = LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port;
	Loc_LCDGPIOcgf.PIN = LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin;
	Loc_LCDGPIOcgf.SPEED = GPIO_SPEED_HIGH;
	GPIO_Init(&Loc_LCDGPIOcgf);

	for(Loc_u8IterVar = 0; Loc_u8IterVar < LCD_DataPinsNumber; Loc_u8IterVar++)
	{
		Loc_LCDGPIOcgf.MODE = GPIO_MODE_PP;
		Loc_LCDGPIOcgf.PORT = LCD_strCfg.LCD_tstrPins.LCD_DataPins[Loc_u8IterVar].LCD_Port;
		Loc_LCDGPIOcgf.PIN = LCD_strCfg.LCD_tstrPins.LCD_DataPins[Loc_u8IterVar].LCD_Pin;
		Loc_LCDGPIOcgf.SPEED = GPIO_SPEED_HIGH;
		GPIO_Init(&Loc_LCDGPIOcgf);
	}

}

static void LCD_vidSendCommand (u8 Copy_u8Command);
void LCD_vidSendCommand (u8 Copy_u8Command)
{

	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_RSPin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_RSPin.LCD_Pin, GPIO_LOW);
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_RWPin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_RWPin.LCD_Pin, GPIO_LOW);

	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[7].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[7].LCD_Pin, GET_BIT(Copy_u8Command,7));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[6].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[6].LCD_Pin, GET_BIT(Copy_u8Command,6));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[5].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[5].LCD_Pin, GET_BIT(Copy_u8Command,5));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[4].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[4].LCD_Pin, GET_BIT(Copy_u8Command,4));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[3].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[3].LCD_Pin, GET_BIT(Copy_u8Command,3));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[2].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[2].LCD_Pin, GET_BIT(Copy_u8Command,2));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[1].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[1].LCD_Pin, GET_BIT(Copy_u8Command,1));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[0].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[0].LCD_Pin, GET_BIT(Copy_u8Command,0));
}


static void LCD_vidSendData(u8 Copy_u8Data);
void LCD_vidSendData(u8 Copy_u8Data)
{

	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_RSPin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_RSPin.LCD_Pin, GPIO_HIGH);
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_RWPin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_RWPin.LCD_Pin, GPIO_LOW);

	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[7].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[7].LCD_Pin, GET_BIT(Copy_u8Data,7));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[6].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[6].LCD_Pin, GET_BIT(Copy_u8Data,6));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[5].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[5].LCD_Pin, GET_BIT(Copy_u8Data,5));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[4].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[4].LCD_Pin, GET_BIT(Copy_u8Data,4));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[3].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[3].LCD_Pin, GET_BIT(Copy_u8Data,3));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[2].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[2].LCD_Pin, GET_BIT(Copy_u8Data,2));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[1].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[1].LCD_Pin, GET_BIT(Copy_u8Data,1));
	GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_DataPins[0].LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_DataPins[0].LCD_Pin, GET_BIT(Copy_u8Data,0));


}



static void LCD_vidGotoXY(u8 LCD_u8XValue, u8 LCD_u8YValue);
void LCD_vidGotoXY(u8 LCD_u8XValue, u8 LCD_u8YValue)
{

	u8 Loc_u8Address = 0;

	Loc_u8Address = (LCD_u8YValue * 0x40) + LCD_u8XValue;
	SET_BIT(Loc_u8Address,7);
	LCD_vidSendCommand(Loc_u8Address);

}


static void LCD_vidInit(void);
void LCD_vidInit(void)
{

	u8 loc_u8EnableValue = 0;

	switch(LCD_enuInitState)
	{
	case Lcd_enuStart:
		Lcd_vidPinInit();
		LCD_enuInitState++;
		break;

	case Lcd_enuFunctionSet:
		GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
		if(!loc_u8EnableValue)
		{
			LCD_u8Command = 0b00111000;
			//LCD_u8Command = LCD_FunctionSet | (LCD_strCfg.LCD_tstrOperation.LCD_enuLinesNumber<<3) | (LCD_strCfg.LCD_tstrOperation.LCD_enuFontCfg<<2) ;
			LCD_vidSendCommand(LCD_u8Command);
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
		}
		else
		{
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
			LCD_enuInitState++;
		}

		break;

	case Lcd_enuDisplayControl:
		GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
		if(!loc_u8EnableValue)
		{
			LCD_u8Command = 0b00001110;
			//LCD_u8Command = LCD_DisplayControl | (LCD_strCfg.LCD_tstrOperation.LCD_strBacklight<<2) | (LCD_strCfg.LCD_tstrOperation.LCD_strCursor<<1) | (LCD_strCfg.LCD_tstrOperation.LCD_strBlinkingCursor<<0);
			LCD_vidSendCommand(LCD_u8Command);
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
		}
		else
		{
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
			LCD_enuInitState++;
		}

		break;
	case Lcd_enuClear:
		GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
		if(!loc_u8EnableValue)
		{
			LCD_u8Command = LCD_ClearScreenMASK;
			LCD_vidSendCommand(LCD_u8Command);
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
		}
		else
		{
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
			LCD_enuInitState++;
		}

		break;
	case Lcd_enuEntryMode:
		GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
		if(!loc_u8EnableValue)
		{
			LCD_u8Command = LCD_EntryModeSetMASK ;
			LCD_vidSendCommand(LCD_u8Command);
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
		}
		else
		{
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
			LCD_enuInitState++;
		}

		break;
	default:

		break;
	}


}


static void Lcd_vidWritingProcess(void);
void Lcd_vidWritingProcess(void)
{

	u8 loc_u8EnableValue = 0;
	u8 Loc_u8Mod = 0;

	switch(Lcd_enuWriteProcess)
	{
	case Lcd_enuWriteData:
		GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
		if(!loc_u8EnableValue)
		{
			LCD_vidSendData(LCD_u8Data);
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
		}
		else
		{
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
			LCD_enuRequest = Lcd_enuNoRequest;
		}
		break;

	case Lcd_enuWriteNumber:

		if(LCD_u16Number == 0)
		{
			GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
			if(!loc_u8EnableValue)
			{
				LCD_vidSendData(48);
				GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
			}
			else
			{
				GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
				LCD_enuRequest = Lcd_enuNoRequest;
			}
		}
		else
		{

			while(LCD_u8ArraySize>0)
			{
				GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
				if(!loc_u8EnableValue)
				{
					Loc_u8Mod = LCD_u8Reversed % 10;
					Loc_u8Mod += 48;  //Adding the 0b00110000 on the number
					LCD_vidSendData(Loc_u8Mod);
					LCD_u8Reversed/=10;
					GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
					LCD_u8ArraySize--;
				}
				else
				{
					GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
				}

			}
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
			LCD_enuRequest = Lcd_enuNoRequest;

		}


		break;

	case Lcd_enuWriteString:


		while(LCD_StringValue[LCD_u8Index] != '\0')
		{
			GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
			if(!loc_u8EnableValue)
			{
				LCD_vidSendData(LCD_StringValue[LCD_u8Index]);
				GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
				LCD_u8Index++;
			}
			else
			{
				GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);

			}

		}
		GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
		LCD_enuRequest = Lcd_enuNoRequest;
		break;

	}


}


static void LCD_vidSendCommandProcess(void);
void LCD_vidSendCommandProcess(void)
{

	u8 loc_u8EnableValue = 0;
	switch(Lcd_enuSendCommand)
	{
	case Lcd_enuGotoXY:
		GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
		if(!loc_u8EnableValue)
		{
			LCD_vidGotoXY(LCD_u8_X,LCD_u8_Y);
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
		}
		else
		{
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
			LCD_enuRequest = Lcd_enuNoRequest;
		}
		break;

	case Lcd_enuClearScreen:
		GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
		if(!loc_u8EnableValue)
		{
			LCD_vidSendCommand(0x01);
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
		}
		else
		{
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
			LCD_enuRequest = Lcd_enuNoRequest;
		}
		break;

	case Lcd_enuSendCommand_Default:
		GPIO_ReadPinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, &loc_u8EnableValue);
		if(!loc_u8EnableValue)
		{
			LCD_vidSendCommand(LCD_u8Command);
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_HIGH);
		}
		else
		{
			GPIO_WritePinValue(LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Port, LCD_strCfg.LCD_tstrPins.LCD_EnablePin.LCD_Pin, GPIO_LOW);
			LCD_enuRequest = Lcd_enuNoRequest;
		}
		break;

	}




}



LCD_tenuErrorStatus LCD_enuSendData (u8 Copy_u8Data)
{
	LCD_tenuErrorStatus Loc_u8State = LCD_enuOk;
	if(LCD_enuRequest == Lcd_enuNoRequest)
	{
		LCD_u8Data = Copy_u8Data;
		LCD_enuRequest = Lcd_enuWritingProcess;
		Lcd_enuWriteProcess = Lcd_enuWriteData;

	}
	else if(LCD_enuRequest == Lcd_enuWritingProcess)
	{
		Loc_u8State = LCD_enuProcessing;
	}
	else
	{
		Loc_u8State = LCD_enuBusy;
	}



	return Loc_u8State;
}


LCD_tenuErrorStatus LCD_enuSendCommand (u8 Copy_u8Command)
{
	LCD_tenuErrorStatus Loc_u8State = LCD_enuOk;
	if(LCD_enuRequest == Lcd_enuNoRequest)
	{
		LCD_u8Command = Copy_u8Command;
		LCD_enuRequest = Lcd_enuSendingCommand;
		Lcd_enuSendCommand = Lcd_enuSendCommand_Default;

	}
	else if(LCD_enuRequest == Lcd_enuSendingCommand)
	{
		Loc_u8State = LCD_enuProcessing;
	}
	else
	{
		Loc_u8State = LCD_enuBusy;
	}


	return Loc_u8State;
}


LCD_tenuErrorStatus LCD_enuGotoXY (u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	LCD_tenuErrorStatus Loc_u8State = LCD_enuOk;

	if(LCD_enuRequest == Lcd_enuNoRequest)
	{

		LCD_u8_X = Copy_u8XPos;
		LCD_u8_Y = Copy_u8YPos;
		LCD_enuRequest = Lcd_enuSendingCommand;
		Lcd_enuSendCommand = Lcd_enuGotoXY;

	}
	else if(LCD_enuRequest == Lcd_enuSendingCommand)
	{
		Loc_u8State = LCD_enuProcessing;
	}
	else
	{
		Loc_u8State = LCD_enuBusy;
	}


	return Loc_u8State;
}


/*LCD_tenuErrorStatus LCD_enuWriteSpecialPattern (u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	LCD_tenuErrorStatus Loc_u8State = LCD_enuOk;
	if(LCD_enuRequest == Lcd_enuNoRequest)
	{
		LCD_u8_X = Copy_u8XPos;
		LCD_u8_Y = Copy_u8YPos;
		LCD_Pattern = Add_pu8Pattern;
		LCD_BlockNumber = Copy_u8BlockNum;

		LCD_enuRequest = Lcd_enuWritingProcess;
		Lcd_enuWriteProcess = Lcd_enuWriteSpecialCharacter;

	}
	else if(LCD_enuRequest == Lcd_enuWritingProcess)
	{
		Loc_u8State = LCD_enuProcessing;
	}
	else
	{
		Loc_u8State = LCD_enuBusy;
	}


	return Loc_u8State;
}

*/

LCD_tenuErrorStatus LCD_enuWriteString (char* Add_pchString)
{
	LCD_tenuErrorStatus Loc_u8State = LCD_enuOk;
	if(LCD_enuRequest == Lcd_enuNoRequest)
	{
		LCD_u8Index = 0;
		LCD_StringValue = Add_pchString;
		LCD_enuRequest = Lcd_enuWritingProcess;
		Lcd_enuWriteProcess = Lcd_enuWriteString;

	}
	else if(LCD_enuRequest == Lcd_enuWritingProcess)
	{
		Loc_u8State = LCD_enuProcessing;
	}
	else
	{
		Loc_u8State = LCD_enuBusy;
	}





	return Loc_u8State;
}


LCD_tenuErrorStatus LCD_enuWriteNumber (u16 Copy_u16Number)
{
	LCD_tenuErrorStatus Loc_u8State = LCD_enuOk;
	u8 Loc_u8Mod = 0;
	u8 Loc_u8ArraySize = 0;
	u8 Loc_u8Reversed = 0;
	u16 Loc_u16CopyNumber = 0;
	if(LCD_enuRequest == Lcd_enuNoRequest)
	{
		LCD_u16Number = Copy_u16Number;
		Loc_u16CopyNumber = Copy_u16Number;
		while (Loc_u16CopyNumber != 0)
		{
			Loc_u8Mod = Loc_u16CopyNumber % 10;
			Loc_u8Reversed = Loc_u8Reversed * 10 + Loc_u8Mod;
			Loc_u8ArraySize++;
			Loc_u16CopyNumber /= 10;
		}
		LCD_u8ArraySize = Loc_u8ArraySize;
		LCD_u8Reversed = Loc_u8Reversed;
		LCD_enuRequest = Lcd_enuWritingProcess;
		Lcd_enuWriteProcess = Lcd_enuWriteNumber;

	}
	else if(LCD_enuRequest == Lcd_enuWritingProcess)
	{
		Loc_u8State = LCD_enuProcessing;
	}
	else
	{
		Loc_u8State = LCD_enuBusy;
	}



	return Loc_u8State;
}


LCD_tenuErrorStatus LCD_enuClearScreen(void)
{
	LCD_tenuErrorStatus Loc_u8State = LCD_enuOk;
	if(LCD_enuRequest == Lcd_enuNoRequest)
	{
		LCD_enuRequest = Lcd_enuSendingCommand;
		Lcd_enuSendCommand = Lcd_enuClearScreen;

	}
	else if(LCD_enuRequest == Lcd_enuSendingCommand)
	{
		Loc_u8State = LCD_enuProcessing;
	}
	else
	{
		Loc_u8State = LCD_enuBusy;
	}



	return Loc_u8State;
}


void LCD_vidTask(void)
{

	if(LCD_enuInitState != Lcd_enuDone)
	{
		LCD_vidInit();
	}
	else
	{
		switch(LCD_enuRequest)
		{
		case Lcd_enuNoRequest:
			break;
		case Lcd_enuWritingProcess:
			Lcd_vidWritingProcess();
			break;
		case Lcd_enuSendingCommand:
			LCD_vidSendCommandProcess();
			break;
		}

	}

}
