/*
 * INT.c
 *
 * Created: 1/26/2023 9:10:51 PM
 *  Author: HP
 */
#include "../../LIB/std_defines.h" 
#include "../../LIB/bit_math.h"
#include "INT.h"
#include "INT_Cfg.h"
#include "INT_piv.h"



static void (*CallBack_Ptr[3])(void) = {NULL};

void __vector_1(void)  __attribute__((signal));
void __vector_2(void)  __attribute__((signal));
void __vector_3(void)  __attribute__((signal));

INT_tenuErrorStatus INT_Init(void)
{

	u8 i;
	INT_tenuErrorStatus state = INT_enuOK;
	
	for(i=0;i<3;i++)
	{
		
	
	switch (i)
	{
		case 0:   //PD2
		if(INT_strPinCfg[i].INT_State == INT_Enabled)
		{
			SET_BIT(GICR,6);
			if(INT_strPinCfg[i].INT_Type == RISING_EDGE)
			{
				SET_BIT(MCUCR,0);
				SET_BIT(MCUCR,1);
			}
			else if(INT_strPinCfg[i].INT_Type == FALLING_EDGE)
			{
				CLR_BIT(MCUCR,0);
				SET_BIT(MCUCR,1);
			}
			else if(INT_strPinCfg[i].INT_Type == LOGICAL_CHANGE)
			{
				SET_BIT(MCUCR,0);
				CLR_BIT(MCUCR,1);
			}
			else if(INT_strPinCfg[i].INT_Type == LOW_LEVEL)
			{
				CLR_BIT(MCUCR,0);
				CLR_BIT(MCUCR,1);
			}
			else
			{
				state = INT_enuNotOK;
			}
		}
		else
		{
			CLR_BIT(GICR,6);
		}
		
		break;
		
		case 1:   //PD3
		
		if(INT_strPinCfg[i].INT_State == INT_Enabled)
		{
		SET_BIT(GICR,7);
		if(INT_strPinCfg[i].INT_Type == RISING_EDGE)
		{
			SET_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		}
		else if(INT_strPinCfg[i].INT_Type == FALLING_EDGE)
		{
			CLR_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		}
		else if(INT_strPinCfg[i].INT_Type == LOGICAL_CHANGE)
		{
			SET_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
		}
		else if(INT_strPinCfg[i].INT_Type == LOW_LEVEL)
		{
			CLR_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
		}
		else
		{
			state = INT_enuNotOK;
		}
		}
		else
		{
			CLR_BIT(GICR,7);
		}
		break;
		
		case 2:   //PB2
		
		if(INT_strPinCfg[i].INT_Type == INT_Enabled)
		{
			
		SET_BIT(GICR,5);
		if(INT_strPinCfg[i].INT_Type == RISING_EDGE)
		{
			SET_BIT(MCUCSR,6);
		}
		else if(INT_strPinCfg[i].INT_Type == FALLING_EDGE)
		{
			CLR_BIT(MCUCSR,6);

		}
		else
		{
			state = INT_enuNotOK;
		}
		}
		else
		{
		CLR_BIT(GICR,5);	
		}
		break;
	}

	}
	
	return state;

}

INT_tenuErrorStatus INT_Enable(u8 Cpy_u8NumberPin)
{
	INT_tenuErrorStatus state = INT_enuOK;
	if(Cpy_u8NumberPin == INT_0)
	{
		SET_BIT(GICR,6);	
		if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == RISING_EDGE)
			{
				SET_BIT(MCUCR,0);
				SET_BIT(MCUCR,1);
			}
			else if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == FALLING_EDGE)
			{
				CLR_BIT(MCUCR,0);
				SET_BIT(MCUCR,1);
			}
			else if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == LOGICAL_CHANGE)
			{
				SET_BIT(MCUCR,0);
				CLR_BIT(MCUCR,1);
			}
			else if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == LOW_LEVEL)
			{
				CLR_BIT(MCUCR,0);
				CLR_BIT(MCUCR,1);
			}
			else
			{
				state = INT_enuNotOK;
			}
	}
	else if(Cpy_u8NumberPin == INT_1)
	{
		SET_BIT(GICR,7);
		if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == RISING_EDGE)
		{
			SET_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		}
		else if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == FALLING_EDGE)
		{
			CLR_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		}
		else if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == LOGICAL_CHANGE)
		{
			SET_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
		}
		else if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == LOW_LEVEL)
		{
			CLR_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
		}
		else
		{
			state = INT_enuNotOK;
		}
	}
	else if(Cpy_u8NumberPin == INT_2)
	{
		SET_BIT(GICR,5);
		if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == RISING_EDGE)
		{
			SET_BIT(MCUCSR,6);
		}
		else if(INT_strPinCfg[Cpy_u8NumberPin].INT_Type == FALLING_EDGE)
		{
			CLR_BIT(MCUCSR,6);

		}
		else
		{
			state = INT_enuNotOK;
		}
	}
	else
	{
		state = INT_enuNotOK;
	}
	return state;
}


INT_tenuErrorStatus INT_Disable(u8 Cpy_u8NumberPin)
{
	INT_tenuErrorStatus state = INT_enuOK;
	if(Cpy_u8NumberPin == INT_0)
	{
		CLR_BIT(GICR,6);
	}
	else if(Cpy_u8NumberPin == INT_1)
	{
		CLR_BIT(GICR,7);
	}
	else if(Cpy_u8NumberPin == INT_2)
	{
		CLR_BIT(GICR,5);
	}
	else
	{
		state = INT_enuNotOK;
	}
	return state;	
}


INT_tenuErrorStatus INT_SetCallback(u8 Cpy_u8INTPinNumber, void(*CpyFuncPtr)(void))
{

	INT_tenuErrorStatus state = INT_enuOK; 
	switch(Cpy_u8INTPinNumber)
	{
	case 0:
	if(CpyFuncPtr != NULL)
	{
		CallBack_Ptr[0] = CpyFuncPtr;		
	}
	else
	{
		state = INT_enuNullPtr;
	}
	break;
	
	case 1:
	if(CpyFuncPtr != NULL)
	{
		CallBack_Ptr[1] = CpyFuncPtr;
	}
	else
	{
		state = INT_enuNullPtr;
	}
	break;
	
	case 2:
	if(CpyFuncPtr != NULL)
	{
		CallBack_Ptr[2] = CpyFuncPtr;
	}
	else
	{
		state = INT_enuNullPtr;
	}
	break;
	}
	return state;
}


void __vector_1(void)
{
	if(CallBack_Ptr[0] != NULL)
	{
		CallBack_Ptr[0]();
	}
	else
	{
		
	}
	
}

void __vector_2(void)
{
	if(CallBack_Ptr[1] != NULL)
	{
		CallBack_Ptr[1]();
	}
	else
	{
	
	}
}


void __vector_3(void)
{
	if(CallBack_Ptr[2] != NULL)
	{
		CallBack_Ptr[2]();
	}
	else
	{
		
	}
	
}