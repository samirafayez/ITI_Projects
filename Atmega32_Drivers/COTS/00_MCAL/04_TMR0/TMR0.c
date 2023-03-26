/*
 * TMR0.c
 *
 * Created: 2/27/2023 3:18:55 AM
 *  Author: HP
 */ 

#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "TMR0.h"
#include "TMR0_Cfg.h"
#include "TMR0_prv.h"
#include <math.h>

f32 TickTime_Ovs =0;
f32 count =0;
f32 Preload_Value =0;

static void (*CallBack_Ptr[2])(void) = {NULL};
	
void __vector_10(void)  __attribute__((signal));
void __vector_11(void)  __attribute__((signal));



TMR0_enuErrorStatus TMR0_vidInitPreCompile(void)
{
	TMR0_enuErrorStatus Loc_u8State =TMR0_enuOK;
	#if ( TMR0_Mode == TMR0_Normal)
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		 
	#elif (TMR0_Mode == TMR0_CTC)
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		
	#elif (TMR0_Mode == TMR0_FASTPWM)
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		
	#elif (TMR0_Mode == TMR0_PHASECORRECTPWM)
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		
	#else
		Loc_u8State =TMR0_enuNotOK;
	
	#endif
	
	TCCR0 &= Waveform_CLR_MASK;
	TCCR0 |= (WAVEFORM<<COM00);
	
	return Loc_u8State;
}

TMR0_enuErrorStatus TMR0_vidInitPostCompile(void)
{
	TMR0_enuErrorStatus Loc_u8State =TMR0_enuOK;
	extern const TMR0Config_t TMR0_strCfg;
	
	if ( TMR0_strCfg.TMR0_MODE == TMR0_enuNormal)
	{
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
	}
	else if(TMR0_strCfg.TMR0_MODE == TMR0_enuCTC)
	{
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);		
	}
	else if(TMR0_strCfg.TMR0_MODE == TMR0_enuFASTPWM)
	{
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);	
	}
	else if (TMR0_strCfg.TMR0_MODE == TMR0_enuPHASECORRECTPWM)
	{
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);		
	}
	else
	{
		return Loc_u8State;
	}

	TCCR0 |= (TMR0_strCfg.TMR0_WAVEFORM<<COM00);
	//TCCR0 |= TMR0_strCfg.TMR0_PRESCALER;
	
	/*PRELOAD Value*/
	TCNT0 = TMR0_strCfg.TMR0_PRELOADVALUE;
	
	return Loc_u8State;
	
	
}
TMR0_enuErrorStatus TMR0_enuSetTickTimeMS(u16 Copy_u16TickTime, u32 Copy_u32Clock)
{
	TMR0_enuErrorStatus Loc_u8State =TMR0_enuOK;

	f32 Loc_f32Clk =0.0;
	f32 Loc_f32Time =0.0;
	f32 Loc_f32Overflowsnumber=0;
	extern const TMR0Config_t TMR0_strCfg;
	if(Copy_u32Clock<=16000000)
	{
		switch(TMR0_strCfg.TMR0_PRESCALER)
		{
			case TMR0_enuNoPrescaling:
				Loc_f32Clk = (f32)Copy_u32Clock/1.0;
				break;
			case TMR0_enuPrescalerCLK_8:
				Loc_f32Clk = (f32)Copy_u32Clock/8.0;
				break;
			case TMR0_enuPrescalerCLK_64:
				Loc_f32Clk = (f32)Copy_u32Clock/64.0;
				break;
			case TMR0_enuPrescalerCLK_256:
				Loc_f32Clk = (f32)Copy_u32Clock/256.0;
				break;
			case TMR0_enuPrescalerCLK_1024:
				Loc_f32Clk = (f32)Copy_u32Clock/1024.0;
				break;
			
		}
		Loc_f32Time = 256/Loc_f32Clk;
		Loc_f32Overflowsnumber = (f32)Copy_u16TickTime/Loc_f32Time;
		TickTime_Ovs = ceil((f32)Loc_f32Overflowsnumber/1000);
		Preload_Value = ceil((TickTime_Ovs - ((f32)Loc_f32Overflowsnumber/1000))*255.0);
		
	}
	else
	{
		Loc_u8State =TMR0_enuNotOK;
	}
		
	return Loc_u8State;
		
}


TMR0_enuErrorStatus TMR0_enuStart(void)
{
	
	TMR0_enuErrorStatus Loc_u8State =TMR0_enuOK;
	TCNT0 = Preload_Value;
	TCCR0 &= Prescaler_CLR_MASK;
	TCCR0 |= TMR0_Prescaler;
	return Loc_u8State;
	
}


TMR0_enuErrorStatus TMR0_enuRegisterCallback( TMR0tenucbf_t Cpy_enucbf,void(*CpyFuncPtr)(void))
{
	
	TMR0_enuErrorStatus Loc_u8State =TMR0_enuOK;
	switch(Cpy_enucbf)
	{
		case 0:
		if(CpyFuncPtr != NULL)
		{
			CallBack_Ptr[0] = CpyFuncPtr;
		}
		else
		{
			Loc_u8State = TMR0_enuNullPtr;
		}
		break;
		
		case 1:
		if(CpyFuncPtr != NULL)
		{
			CallBack_Ptr[1] = CpyFuncPtr;
		}
		else
		{
			Loc_u8State = TMR0_enuNullPtr;
		}
		break;

	}
	return Loc_u8State;
}
	

TMR0_enuErrorStatus TMR0_OCInterruptEnable(void)
{
	TMR0_enuErrorStatus Loc_u8State = TMR0_enuOK;
	SET_BIT(TIMSK,OCIE0);
	return Loc_u8State;
	
}
TMR0_enuErrorStatus TMR0_OVInterruptEnable(void)
{
	TMR0_enuErrorStatus Loc_u8State = TMR0_enuOK;
	SET_BIT(TIMSK,TOIE0);
	return Loc_u8State;
	
}


/*compare match ISR*/
void __vector_10(void)
{
	SET_BIT(TIFR,1);
	if(CallBack_Ptr[0] != NULL)
	{
		CallBack_Ptr[0]();
	}
	else
	{
	
	}
	
}

/*overflow ISR*/
void __vector_11(void)
{
	SET_BIT(TIFR,0);
	
	if(CallBack_Ptr[1] != NULL)
	{
			count++;
			if(count == TickTime_Ovs)
			{
				CallBack_Ptr[1]();
				count=0;
				TCNT0 = Preload_Value;
			}
	}
	else
	{

	}

}


TMR0_enuErrorStatus TMR0_ForceCompareEN(void)
{
	TMR0_enuErrorStatus	Loc_u8State = TMR0_enuOK;
	SET_BIT(TCCR0,FOC0);
	
	return Loc_u8State;
}
TMR0_enuErrorStatus TMR0_ForceCompareDIS(void)
{
	TMR0_enuErrorStatus	Loc_u8State = TMR0_enuOK;
	CLR_BIT(TCCR0,FOC0);
		
	return Loc_u8State;
	
}


TMR0_enuErrorStatus TMR0_SetCompareMatch(u8 Cpy_u8CompareMatchVal)
{
	TMR0_enuErrorStatus	Loc_u8State = TMR0_enuOK;
	ASSIGN_REG(OCR0,Cpy_u8CompareMatchVal);
	
	return Loc_u8State;
}





TMR0_enuErrorStatus TMR0_enuSetDutyCycle(f32 Cpy_f32DutyCycle)
{
	TMR0_enuErrorStatus Loc_u8State = TMR0_enuOK;
	u8 Loc_u8OCvalue=0;
	
	extern const TMR0Config_t TMR0_strCfg;

	if(TMR0_strCfg.TMR0_WAVEFORM == OC0_enuNONINVERTING)
	{
		Loc_u8OCvalue = Cpy_f32DutyCycle * 255;
		TMR0_SetCompareMatch(Loc_u8OCvalue);
	}
	else if(TMR0_strCfg.TMR0_WAVEFORM == OC0_enuINVERTING)
	{
		Cpy_f32DutyCycle =1-Cpy_f32DutyCycle;
		Loc_u8OCvalue = Cpy_f32DutyCycle * 255;
		TMR0_SetCompareMatch(Loc_u8OCvalue);
	}
	else
	{
		Loc_u8State = TMR0_enuNotOK;
	}
	
	
	return Loc_u8State;
	
}