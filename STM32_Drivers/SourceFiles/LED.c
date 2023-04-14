/*
 * LED.c
 *
 *  Created on: Feb 23, 2023
 *      Author: HP
 */

#include "std_defines.h"
#include "bit_math.h"
#include "00_LED/LED.h"
#include "00_LED/LED_prv.h"
#include "01_GPIO/GPIO.h"



LED_tenuErrorStatus LED_Init(void)
{
	LED_tenuErrorStatus Loc_u8State = LED_enuOK;

	GPIOcgf_t Loc_GPIOcgf_InitCfg;
	u8 Loc_u8IterVar;
	extern const LED_tstrLEDcfg LED_strLEDcfg[LED_enuNumberOfLEDs];
	for(Loc_u8IterVar = 0; Loc_u8IterVar<LED_enuNumberOfLEDs; Loc_u8IterVar++)
	{
		Loc_GPIOcgf_InitCfg.MODE = GPIO_MODE_PP;
		Loc_GPIOcgf_InitCfg.SPEED = LED_strLEDcfg[Loc_u8IterVar].LED_SPEED;
		Loc_GPIOcgf_InitCfg.PORT = LED_strLEDcfg[Loc_u8IterVar].LED_PORT;
		Loc_GPIOcgf_InitCfg.PIN = LED_strLEDcfg[Loc_u8IterVar].LED_PIN;
		GPIO_Init(&Loc_GPIOcgf_InitCfg);
	}

	return Loc_u8State;
}

LED_tenuErrorStatus LED_enuLEDon(LED_tenuLEDNames Cpy_u8LEDName)
{

	LED_tenuErrorStatus Loc_u8State = LED_enuOK;

	if(Cpy_u8LEDName<LED_enuNumberOfLEDs)
	{
		extern const LED_tstrLEDcfg LED_strLEDcfg[LED_enuNumberOfLEDs];

		if(LED_strLEDcfg[Cpy_u8LEDName].LED_Mode == LED_ACTIVE_HIGH)
		{
			GPIO_WritePinValue(LED_strLEDcfg[Cpy_u8LEDName].LED_PORT, LED_strLEDcfg[Cpy_u8LEDName].LED_PIN , GPIO_HIGH);

		}
		else
		{
			GPIO_WritePinValue(LED_strLEDcfg[Cpy_u8LEDName].LED_PORT, LED_strLEDcfg[Cpy_u8LEDName].LED_PIN , GPIO_LOW);
		}
	}
	else
	{
		Loc_u8State = LED_enuNotOK;
	}
	return Loc_u8State;
}



LED_tenuErrorStatus LED_enuLEDoff(LED_tenuLEDNames Cpy_u8LEDName)
{

	LED_tenuErrorStatus Loc_u8State = LED_enuOK;

	if(Cpy_u8LEDName<LED_enuNumberOfLEDs)
	{
		extern const LED_tstrLEDcfg LED_strLEDcfg[LED_enuNumberOfLEDs];

		if(LED_strLEDcfg[Cpy_u8LEDName].LED_Mode == LED_ACTIVE_HIGH)
		{
			GPIO_WritePinValue(LED_strLEDcfg[Cpy_u8LEDName].LED_PORT, LED_strLEDcfg[Cpy_u8LEDName].LED_PIN , GPIO_LOW);
		}
		else
		{
			GPIO_WritePinValue(LED_strLEDcfg[Cpy_u8LEDName].LED_PORT, LED_strLEDcfg[Cpy_u8LEDName].LED_PIN , GPIO_HIGH);
		}
	}
	else
	{
		Loc_u8State = LED_enuNotOK;
	}
	return Loc_u8State;
}



LED_tenuErrorStatus LED_enuLEDToggle(LED_tenuLEDNames Cpy_u8LEDName)
{

	LED_tenuErrorStatus Loc_u8State = LED_enuOK;

	if(Cpy_u8LEDName<LED_enuNumberOfLEDs)
	{
		extern const LED_tstrLEDcfg LED_strLEDcfg[LED_enuNumberOfLEDs];

		GPIO_TogglePinValue(LED_strLEDcfg[Cpy_u8LEDName].LED_PORT,LED_strLEDcfg[Cpy_u8LEDName].LED_PIN);

	}
	else
	{
		Loc_u8State = LED_enuNotOK;
	}
	return Loc_u8State;

}
