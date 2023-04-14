/*
 * Systick.c
 *
 *  Created on: Mar 25, 2023
 *      Author: HP
 */


#include "std_defines.h"
#include "bit_math.h"
#include "03_Systick/Systick.h"
#include "03_Systick/Systick_Cfg.h"
#include "03_Systick/Systick_prv.h"
#include <math.h>



static void(*Systick_CallBackPtr)(void) = NULL;


extern const Systick_tstrCFG Systick_strcfg;

static volatile u32 Systick_Count = 0;
static volatile u32 Systick_PreLoadValue = 0;


Systick_tenuErrorStatus Systick_vidInit(void)
{
	Systick_tenuErrorStatus Loc_u8State = Systick_enuOk;

	Systick->CTRL = 0;
	/*Enabling Systick Timer Interrupt*/
	SET_BIT(Systick->CTRL, TickInt);

	if(Systick_strcfg.Systick_enuClkSrc == Systick_EXT_Clk)
	{
		SET_BIT(Systick->CTRL, CLKSRC);
	}
	else if(Systick_strcfg.Systick_enuClkSrc == Systick_EXTClkDividedBy8)
	{
		CLR_BIT(Systick->CTRL, CLKSRC);
	}
	else
	{
		Loc_u8State = Systick_enuNotOk;
	}

	ASSIGN_REG(Systick->LOAD, (Systick_strcfg.Systick_Load & Systick_MAXVALUEMASK));
	Systick->VAL = 0;

	return Loc_u8State;

}



Systick_tenuErrorStatus Systick_vidSetTime(u32 Copy_u32MilliSecond)
{
	Systick_tenuErrorStatus Loc_u8State = Systick_enuOk;
	f32 Loc_f32TimerClk = 0.0;
	f32 Loc_f32Time = 0.0;
	f32 Loc_f32UnderFlows = 0.0;
	f32 Loc_f32Seconds = (f32)Copy_u32MilliSecond/1000;

	if(Systick_strcfg.Systick_enuClkSrc == Systick_EXT_Clk)
	{
		Loc_f32TimerClk = (f32)CLK_FREQUENCY;
	}
	else
	{
		Loc_f32TimerClk = (f32)CLK_FREQUENCY/8 ;
	}

	Loc_f32Time = (Systick_strcfg.Systick_Load+1)/Loc_f32TimerClk;
	Loc_f32UnderFlows = (f32)Loc_f32Seconds/Loc_f32Time;
	Systick_Count = ceil(Loc_f32UnderFlows);
	Systick_PreLoadValue = (Systick_strcfg.Systick_Load) - ceil((Systick_Count-Loc_f32UnderFlows)*(Systick_strcfg.Systick_Load));
	ASSIGN_REG(Systick->LOAD, Systick_PreLoadValue);

	return Loc_u8State;

}


Systick_tenuErrorStatus Systick_vidStart(void)
{

	Systick_tenuErrorStatus Loc_u8State = Systick_enuOk;

	/*Enabling Systick Timer*/
	//ASSIGN_REG(Systick->LOAD, Systick_PreLoadValue);
	SET_BIT(Systick->CTRL, Systick_EN);


	return Loc_u8State;

}


Systick_tenuErrorStatus Systick_vidRegisterCallBack( void(*Cpy_CallBackFunc)(void))
{

	Systick_tenuErrorStatus Loc_u8State = Systick_enuOk;
	if(Cpy_CallBackFunc != NULL)
	{
		Systick_CallBackPtr = Cpy_CallBackFunc;
	}
	else
	{
		Loc_u8State = Systick_enuNullPtr;
	}

	return Loc_u8State;

}


void SysTick_Handler(void)
{
	static u8 Loc_count =0;

	if(Systick_CallBackPtr != NULL)
	{
		Loc_count++ ;
		if(Loc_count == Systick_Count)
		{
			Systick_CallBackPtr();
			Loc_count=0;
			ASSIGN_REG(Systick->VAL, 0);
		}
		else
		{

		}
	}
	else
	{

	}


}
