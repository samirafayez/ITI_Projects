/*
 * TMR1.c
 *
 * Created: 3/12/2023 12:11:16 AM
 *  Author: HP
 */

#define F_CPU 1000000UL
#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h" 
#include "TMR1.h"
#include "TMR1_Cfg.h"
#include "TMR1_prv.h"
#include <math.h>

static volatile f32 TickTime_Ovs = 0;
static volatile f32 count = 0;
static volatile f32 Preload_Value = 0;

static void (*CallBack_Ptr_OF)(void) = NULL;
static void (*CallBack_Ptr_IC)(void) = NULL;
static void (*CallBack_Ptr_OCA)(void) = NULL;

/*Capture Unit ISR*/
void __vector_6(void)  __attribute__((signal));
void __vector_6(void)
{
	SET_BIT(TIFR,ICF1);
	
	if(CallBack_Ptr_IC != NULL)
	{
		CallBack_Ptr_IC();
	}
	else
	{
		
	}
}

/*OCA ISR*/ 
void __vector_7(void)  __attribute__((signal));
void __vector_7(void)
{
	SET_BIT(TIFR,OCF1A);
	if( CallBack_Ptr_OCA != NULL)
	{
		CallBack_Ptr_OCA();
	}
	else
	{
		
	}
}

/*OVS ISR*/
void __vector_9(void)  __attribute__((signal));
void __vector_9(void)
{
	SET_BIT(TIFR,TOV1);
	if(CallBack_Ptr_OF != NULL)
	{
		count++;
		if(count == TickTime_Ovs)
		{
			CallBack_Ptr_OF();
			count = 0;
			TCNT1 = Preload_Value;
		}
	}
	else
	{
		
	}
}
TMR1_tenuErrorStatus TMR1_vidInit(void)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	switch(TMR1_MODE)
	{
		case TMR1_Normal:
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_PWM_PhaseCorrect_8bit:
			SET_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_PWM_PhaseCorrect_9bit:
			CLR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_PWM_PhaseCorrect_10bit:
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_CTC_OCR:
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_Fast_PWM_8bit:
			SET_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_Fast_PWM_9bit:
			CLR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_Fast_PWM_10bit:
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_PWM_PhaseFrequency_Correct_ICR:
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_PWM_PhaseFrequency_Correct_OCR:
			SET_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_PWM_PhaseCorrect_ICR:
			CLR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_PWM_PhaseCorrect_OCR:
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_CTC_ICR:
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_Fast_PWM_ICR:
			CLR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
			
		case TMR1_Fast_PWM_OCR:
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;	
	}
	
	TCCR1A &= Waveform_CLR_MASK_A;
	TCCR1A |= (TMR1_Waveform<<COM1A0);

	#if (TMR1_Noise_Cancellation == TMR1_Enabled)
		SET_BIT(TCCR1B,ICNC1);
	#elif (TMR1_Noise_Cancellation == TMR1_Disabled)
		CLR_BIT(TCCR1B,ICNC1);
	#else
		Loc_u8State = TMR1_enuNotOK;
	#endif
	
	#if (TMR1_Input_Capture_Select == TMR1_FallingEdge)
		CLR_BIT(TCCR1B,ICES1);
	#elif (TMR1_Input_Capture_Select == TMR1_RisingEdge)
		SET_BIT(TCCR1B,ICES1);
	#else 
		Loc_u8State = TMR1_enuNotOK;
	#endif
	
	return Loc_u8State;
}


TMR1_tenuErrorStatus TMR1_enuRegisterCallback(TMR1tenucbf_t Cpy_enucbf, void(*CpyFuncPtr)(void))
{
	
	TMR1_tenuErrorStatus Loc_u8State =TMR1_enuOK;
	if(CpyFuncPtr != NULL)
	{
		switch (Cpy_enucbf)
		{
			case TMR1_enuInputCapture:
				CallBack_Ptr_IC = CpyFuncPtr;
				break;
			case TMR1_enuOverflow:
				CallBack_Ptr_OF = CpyFuncPtr;
				break;		
			case TMR1_enuCompareOutA:
				CallBack_Ptr_OCA = CpyFuncPtr;
				break;
		}
	}
	else
	{
		Loc_u8State = TMR1_enuNullPtr;
	}

	return Loc_u8State;
}

TMR1_tenuErrorStatus TMR1_enuSetTickTimeMS(u16 Copy_u16TickTime, u32 Copy_u32Clock)
{
	TMR1_tenuErrorStatus Loc_u8State =TMR1_enuOK;

	f32 Loc_f32Clk =0.0;
	f32 Loc_f32Time =0.0;
	f32 Loc_f32Overflowsnumber=0;
	if(Copy_u32Clock<=16000000)
	{
		switch(TMR1_Prescaler)
		{
			case TMR1_NoPrescaling:
			Loc_f32Clk = (f32)Copy_u32Clock/1.0;
			break;
			case TMR1_Prescaler_8:
			Loc_f32Clk = (f32)Copy_u32Clock/8.0;
			break;
			case TMR1_Prescaler_64:
			Loc_f32Clk = (f32)Copy_u32Clock/64.0;
			break;
			case TMR1_Prescaler_256:
			Loc_f32Clk = (f32)Copy_u32Clock/256.0;
			break;
			case TMR1_Prescaler_1024:
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
		Loc_u8State =TMR1_enuNotOK;
	}
	
	return Loc_u8State;
	
}
TMR1_tenuErrorStatus TMR1_enuStart(void)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	if(TMR1_Prescaler<8)
	{
		TCCR1B &= Prescaler_CLR_MASK;
		TCCR1B |= TMR1_Prescaler;
	}
	else
	{
		Loc_u8State = TMR1_enuNotOK;
	}
	
	return Loc_u8State;
}

TMR1_tenuErrorStatus TMR1_ICUInterruptEnable(void)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	SET_BIT(TIMSk,TICIE1);
	return Loc_u8State;
	
}

TMR1_tenuErrorStatus TMR1_OFInterruptEnable(void)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	SET_BIT(TIMSk,TOIE1);
	return Loc_u8State;
	
}

TMR1_tenuErrorStatus TMR1_OCAInterruptEnable(void)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	SET_BIT(TIMSk,OCIE1A);
	return Loc_u8State;
	
}

TMR1_tenuErrorStatus TMR1_OFInterruptDisable(void)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	CLR_BIT(TIMSk,TOIE1);
	
	return Loc_u8State;
	
}

TMR1_tenuErrorStatus TMR1_ICUInterruptDisable(void)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	CLR_BIT(TIMSk,TICIE1);
	
	return Loc_u8State;	
}


TMR1_tenuErrorStatus TMR1_enuReadICR(u16 * Add_pu16ICRValue)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	if(Add_pu16ICRValue != NULL)
	{
		*Add_pu16ICRValue = ICR1;
	}
	else
	{
		Loc_u8State = TMR1_enuNullPtr;
	}
	
	return Loc_u8State;
}


TMR1_tenuErrorStatus TMR1_enuSetTCNT1(u16 Cpy_u16TCNT1Value)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	TCNT1 = Cpy_u16TCNT1Value;
	return Loc_u8State;
	
}

TMR1_tenuErrorStatus TMR1_enuSetICR1(u16 Cpy_u16ICRValue)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	ICR1 = Cpy_u16ICRValue;
	return Loc_u8State;
	
}

TMR1_tenuErrorStatus TMR1_SetCompareMatchOCA(u16 Cpy_u16CompareMatchVal)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	ASSIGN_REG(OCR1A,Cpy_u16CompareMatchVal);
	return Loc_u8State;
}

TMR1_tenuErrorStatus TMR1_enuSetDutyCycle(f32 Cpy_f32DutyCycle)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	u16 Loc_f16OCvalue=0;
	if(TMR1_Waveform == FastPWM_OC1_NONINVERTING)
	{
		Loc_f16OCvalue = Cpy_f32DutyCycle * 255;
	}
	else if(TMR1_Waveform == FastPWM_OC1_INVERTING)
	{
		Cpy_f32DutyCycle = 1-Cpy_f32DutyCycle;
		Loc_f16OCvalue = Cpy_f32DutyCycle * 255;
	}
	else
	{
		Loc_u8State = TMR1_enuNotOK;
	}
	
	TMR1_SetCompareMatchOCA(Loc_f16OCvalue);
	
	return Loc_u8State;
	
}


TMR1_tenuErrorStatus TMR1_enuRisingEdgeSel(void)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	SET_BIT(TCCR1B,ICES1);
	return Loc_u8State;
}
TMR1_tenuErrorStatus TMR1_enuFallingEdgeSel(void)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	CLR_BIT(TCCR1B,ICES1);
	return Loc_u8State;
}


TMR1_tenuErrorStatus TMR1_enuCalculate_Time(u16 Cpy_ICRValue, f32 * Add_f32Time)
{
	TMR1_tenuErrorStatus Loc_u8State = TMR1_enuOK;
	f32 Loc_f32Clk =0.0;
	f32 Loc_f32Time =0.0;

	switch(TMR1_Prescaler)
	{
		case TMR1_NoPrescaling:
			Loc_f32Clk = (f32)F_CPU/1.0;
			break;
		case TMR1_Prescaler_8:
			Loc_f32Clk = (f32)F_CPU/8.0;
			break;
		case TMR1_Prescaler_64:
			Loc_f32Clk = (f32)F_CPU/64.0;
			break;
		case TMR1_Prescaler_256:
			Loc_f32Clk = (f32)F_CPU/256.0;
			break;
		case TMR1_Prescaler_1024:
			Loc_f32Clk = (f32)F_CPU/1024.0;
			break;
			
		}
		
		Loc_f32Time = (f32)Cpy_ICRValue/Loc_f32Clk;
		*Add_f32Time = (Loc_f32Time*1000000);
	
	return Loc_u8State;
}


