/*
 * PUSH_BUTTON.c
 *
 *  Created on: Feb 24, 2023
 *      Author: HP
 */


#include "std_defines.h"
#include "bit_math.h"
#include "01_PUSHBUTTON/PUSHBUTTON.h"
#include "01_PUSHBUTTON/PUSHBUTTON_prv.h"
#include "01_GPIO/GPIO.h"
#include "00_Scheduler/Scheduler.h"

static volatile u8 SwitchStatus[PUSHBUTTON_enuNumberOfPUSHBUTTONs] = {0};
extern const PUSHBUTTON_tstrPUSHBUTTONcfg PUSHBUTTON_strPUSHBUTTONcfg[PUSHBUTTON_enuNumberOfPUSHBUTTONs];




PUSHBUTTON_tenuErrorStatus PUSHBUTTON_enuPUSHBUTTON_Init(void)
{
	PUSHBUTTON_tenuErrorStatus Loc_u8State = PUSHBUTTON_enuOK;
	GPIOcgf_t Loc_GPIOcgf_InitCfg;
	u8 Loc_u8IterVar;


	for(Loc_u8IterVar = 0; Loc_u8IterVar<PUSHBUTTON_enuNumberOfPUSHBUTTONs; Loc_u8IterVar++)
	{
		Loc_GPIOcgf_InitCfg.MODE = PUSHBUTTON_strPUSHBUTTONcfg[Loc_u8IterVar].PUSHBUTTON_MODE;
		Loc_GPIOcgf_InitCfg.SPEED = PUSHBUTTON_strPUSHBUTTONcfg[Loc_u8IterVar].PUSHBUTTON_SPEED;
		Loc_GPIOcgf_InitCfg.PORT = PUSHBUTTON_strPUSHBUTTONcfg[Loc_u8IterVar].PUSHBUTTON_PORT;
		Loc_GPIOcgf_InitCfg.PIN = PUSHBUTTON_strPUSHBUTTONcfg[Loc_u8IterVar].PUSHBUTTON_PIN;
		GPIO_Init(&Loc_GPIOcgf_InitCfg);

	}

	return Loc_u8State;
}





void PUSHBUTTON_enuPUSHBUTTON_Read(void)
{

	u8 Loc_u8Iteration;
	u8  Loc_pu8_PinValue[PUSHBUTTON_enuNumberOfPUSHBUTTONs] = {0};
	static u8 Loc_u8Counter[PUSHBUTTON_enuNumberOfPUSHBUTTONs] = {0};
	static u8 Loc_u8PrevStatus[PUSHBUTTON_enuNumberOfPUSHBUTTONs] = {0};


	for(Loc_u8Iteration = 0; Loc_u8Iteration < PUSHBUTTON_enuNumberOfPUSHBUTTONs; Loc_u8Iteration++)
	{


		GPIO_ReadPinValue (PUSHBUTTON_strPUSHBUTTONcfg[Loc_u8Iteration].PUSHBUTTON_PORT,  PUSHBUTTON_strPUSHBUTTONcfg[Loc_u8Iteration].PUSHBUTTON_PIN, &Loc_pu8_PinValue[Loc_u8Iteration]);
		if (Loc_pu8_PinValue[Loc_u8Iteration] == Loc_u8PrevStatus[Loc_u8Iteration])
		{
			Loc_u8Counter[Loc_u8Iteration]++;
		}
		else
		{
			Loc_u8Counter[Loc_u8Iteration] = 0;
			SwitchStatus[Loc_u8Iteration] = 0;
		}


		if(Loc_u8Counter[Loc_u8Iteration] == 5)
		{
			Loc_u8Counter[Loc_u8Iteration] = 0;
			SwitchStatus[Loc_u8Iteration] = 1;
		}
		else
		{

		}

		Loc_u8PrevStatus[Loc_u8Iteration] = 1;


	}
}




PUSHBUTTON_tenuErrorStatus PUSHBUTTON_enuPUSHBUTTON_ReturnState(PUSHBUTTON_tenuPUSHBUTTONNames PUSHBUTTON_enuPUSHBUTTONName, u8* Add_pu8_PinValue)
{

	PUSHBUTTON_tenuErrorStatus Loc_u8State = PUSHBUTTON_enuOK;

	if(PUSHBUTTON_strPUSHBUTTONcfg[PUSHBUTTON_enuPUSHBUTTONName].PUSHBUTTON_MODE == PUSHBUTTON_PULLUP)
	{
		if(SwitchStatus[PUSHBUTTON_enuPUSHBUTTONName] == 1 )
		{
			* Add_pu8_PinValue = 0;
		}
		else
		{
			* Add_pu8_PinValue = 1;
		}

	}
	return Loc_u8State;
}
