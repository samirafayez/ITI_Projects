/*
 * NVIC.c
 *
 *  Created on: Mar 2, 2023
 *      Author: HP
 */

#include "std_defines.h"
#include "bit_math.h"
#include "02_NVIC/NVIC.h"
#include "02_NVIC/NVIC_Cfg.h"
#include "02_NVIC/NVIC_prv.h"



static void (*CallBackPtrEXT)(void) = {NULL};


/*NVIC_tenuErrorStatus NVIC_GlobalInterruptEN(void)
{
	NVIC_tenuErrorStatus Loc_u8State = NVIC_enuOk;



	return Loc_u8State;
}
 */

NVIC_tenuErrorStatus NVIC_enuDisable(IRQtenu_number Cpy_IRQn)
{
	NVIC_tenuErrorStatus Loc_u8State = NVIC_enuOk;

	if((Cpy_IRQn<NVIC_IRQnumber) && (Cpy_IRQn >= 0))
	{
		SET_BIT(NVIC->ICER[Cpy_IRQn/32],(Cpy_IRQn%32));
	}
	else
	{
		Loc_u8State = NVIC_enuNotOk;
	}

	return Loc_u8State;
}
NVIC_tenuErrorStatus NVIC_enuEnable(IRQtenu_number Cpy_IRQn)
{
	NVIC_tenuErrorStatus Loc_u8State = NVIC_enuOk;
	u8 Loc_u8RegisterNum = 0;
	u8 Loc_u8BitNum = 0;
	Loc_u8RegisterNum = Cpy_IRQn/32;
	Loc_u8BitNum = Cpy_IRQn%32;
	if((Cpy_IRQn<NVIC_IRQnumber) && (Cpy_IRQn >= 0))
	{
		SET_BIT(NVIC->ISER[Loc_u8RegisterNum],Loc_u8BitNum);
	}
	else
	{
		Loc_u8State = NVIC_enuNotOk;
	}
	return Loc_u8State;
}

NVIC_tenuErrorStatus NVIC_enuGetActiveStatus(IRQtenu_number Cpy_IRQn, u32 * Cpy_u32Status)
{
	NVIC_tenuErrorStatus Loc_u8State = NVIC_enuOk;
	u8 Loc_u8RegisterNum = 0;
	u8 Loc_u8BitNum = 0;
	Loc_u8RegisterNum = Cpy_IRQn/32;
	Loc_u8BitNum = Cpy_IRQn%32;

	if((Cpy_u32Status != NULL) && (Cpy_IRQn < NVIC_IRQnumber) && (Cpy_IRQn >= 0))
	{
		* Cpy_u32Status = GET_BIT(NVIC->IABR[Loc_u8RegisterNum],Loc_u8BitNum);
	}
	else
	{
		Loc_u8State = NVIC_enuNullPtr;
	}

	return Loc_u8State;
}
NVIC_tenuErrorStatus NVIC_enuSetPending(IRQtenu_number Cpy_IRQn)
{
	NVIC_tenuErrorStatus Loc_u8State = NVIC_enuOk;
	u8 Loc_u8RegisterNum = 0;
	u8 Loc_u8BitNum = 0;
	Loc_u8RegisterNum = Cpy_IRQn/32;
	Loc_u8BitNum = Cpy_IRQn%32;

	if((Cpy_IRQn<NVIC_IRQnumber) && (Cpy_IRQn >= 0))
	{
		SET_BIT(NVIC->ISPR[Loc_u8RegisterNum],Loc_u8BitNum);
	}
	else
	{
		Loc_u8State = NVIC_enuNotOk;
	}


	return Loc_u8State;
}
NVIC_tenuErrorStatus NVIC_enuClearPending(IRQtenu_number Cpy_IRQn)
{
	NVIC_tenuErrorStatus Loc_u8State = NVIC_enuOk;
	u8 Loc_u8RegisterNum = 0;
	u8 Loc_u8BitNum = 0;
	Loc_u8RegisterNum = Cpy_IRQn/32;
	Loc_u8BitNum = Cpy_IRQn%32;

	if((Cpy_IRQn<NVIC_IRQnumber) && (Cpy_IRQn >= 0))
	{
		SET_BIT(NVIC->ICPR[Loc_u8RegisterNum],Loc_u8BitNum);
	}
	else
	{
		Loc_u8State = NVIC_enuNotOk;
	}

	return Loc_u8State;
}
NVIC_tenuErrorStatus NVIC_enuSetPriority(IRQtenu_number Cpy_IRQn, u32 Cpy_u32Priority)
{
	NVIC_tenuErrorStatus Loc_u8State = NVIC_enuOk;

	if((Cpy_IRQn<NVIC_IRQnumber) && (Cpy_IRQn >= 0))
	{
		ASSIGN_REG(NVIC->IPR[Cpy_IRQn/4],(Cpy_u32Priority<<(8*(Cpy_IRQn%4)))+4);
	}
	else
	{
		Loc_u8State = NVIC_enuNotOk;
	}
	return Loc_u8State;
}




/*Just for testing*/
NVIC_tenuErrorStatus NVIC_SetCallBackFunction(IRQtenu_number Cpy_IRQn, void(*Cpy_CallBackPtr)(void))
{
	NVIC_tenuErrorStatus Loc_u8State = NVIC_enuOk;
	if((Cpy_IRQn<NVIC_IRQnumber) &&(Cpy_CallBackPtr != NULL) && (Cpy_IRQn >= 0))
	{
		CallBackPtrEXT = Cpy_CallBackPtr;
	}
	else
	{

	}
	return Loc_u8State;
}



void EXTI0_IRQHandler(void)
{

	if(CallBackPtrEXT != NULL)
	{
		CallBackPtrEXT();
	}
	else
	{

	}

}


/*NVIC_tenuErrorStatus NVIC_SetPriorityGrouping(u32 Cpy_u32GroupingPriority)
{
	NVIC_tenuErrorStatus Loc_u8State = NVIC_enuOk;

	return Loc_u8State;
}
 */
