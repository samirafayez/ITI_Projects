/*
 * ADC.c
 *
 * Created: 2/7/2023 6:52:54 PM
 *  Author: HP
 */ 
#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "ADC.h"
#include "ADC_Cfg.h"
#include "ADC_prv.h"


static void(*CallbackPtr_EOJ)(void) = NULL;
static u16 * ADD_pu16ADCValue = NULL;

ADC_tenuErrorStatus ADC_enuInit(void)
{
	
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOk;
	
	/*ADC Reference*/
	#if (ADC_Vref == VCC)
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		
	#elif (ADC_Vref == InternalVref)
		SET_BIT(ADMUX,REFS0);	
		SET_BIT(ADMUX,REFS1);

	#elif (ADC_Vref == NOVref)
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		
	#else
		Loc_u8State = ADC_enuNotOk;
		
	#endif
	
	 
	/*ADC Enabling*/
	#if (ADC_ENABLE == ADC_ON)
		SET_BIT(ADCSRA, ADEN);
		
	#elif (ADC_ENABLE == ADC_OFF)
		CLR_BIT(ADCSRA, ADEN);
	
	#else
		Loc_u8State = ADC_enuNotOk;
		
	#endif
	
	/*PrescalerValue*/
	#if (ADC_PrescalerValue == ADC_PS_2)
		CLR_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif (ADC_PrescalerValue == ADC_PS_4)
		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif (ADC_PrescalerValue == ADC_PS_8)
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif (ADC_PrescalerValue == ADC_PS_16)
		CLR_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif (ADC_PrescalerValue == ADC_PS_32)
		SET_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif (ADC_PrescalerValue == ADC_PS_64)
		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif (ADC_PrescalerValue == ADC_PS_128)
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#else
		Loc_u8State = ADC_enuNotOk;
	#endif		
	
	
	/*AutoTrigger*/
	#if (ADC_AutoTriggerEN == ADC_ON)
		SET_BIT(ADCSRA,ADATE);
		#if ((ADC_AutoTriggerSrc>=0) && (ADC_AutoTriggerSrc<8))
			SFIOR &= ADC_AutoTrigger_CLR_MASK;
			SFIOR |= (ADC_AutoTriggerSrc<<5);
		#else
			Loc_u8State = ADC_enuNotOk;
		#endif
		
	#elif (ADC_AutoTriggerEN == ADC_OFF)
		CLR_BIT(ADCSRA,ADATE);
		
	#else
		Loc_u8State = ADC_enuNotOk;
		
	#endif
	
	/*ADC Result Adjustment*/
	
	#if (ADC_Adjustment == ADC_Right)
		CLR_BIT(ADMUX,ADLAR);
	#elif (ADC_Adjustment == ADC_Left)
		SET_BIT(ADMUX,ADLAR);
	#else
		Loc_u8State = ADC_enuNotOk;
		
	#endif
	
	
	return Loc_u8State; 
	
}

ADC_tenuErrorStatus ADC_enuSelectChannel( ADC_tenuChannelNumber Cpy_u8ChannelNumber)
{
	
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOk;
	if((Cpy_u8ChannelNumber>=0) && (Cpy_u8ChannelNumber<8))
	{
		ADMUX &= ADC_ADMUX_CLR_MASK;
		ADMUX |= Cpy_u8ChannelNumber;
	}
	else
	{
		Loc_u8State = ADC_enuNotOk;
	}
	
	return Loc_u8State;
}


ADC_tenuErrorStatus ADC_enuSynchGetADCValue( u16 * Add_pu16ADCValue)
{
	
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOk;
	u16 Loc_u16Result = 0;
	
	//SET_BIT(ADCSRA,ADIF);
	/*Start Conversion*/
	SET_BIT(ADCSRA,ADSC);
	
	
	#if (ADC_AutoTriggerEN == ADC_ON)
	while(!((ADCSRA>>ADIF)&1));
	#elif (ADC_AutoTriggerEN == ADC_OFF)
	while(((ADCSRA>>ADSC)&1));
	#endif

	if(Add_pu16ADCValue != NULL)  
	{
		#if (ADC_Adjustment == ADC_Right)
			*Add_pu16ADCValue = ADCL;
			Loc_u16Result = ADCH;
			*Add_pu16ADCValue |= (Loc_u16Result<<8);
		#elif (ADC_Adjustment == ADC_Left)
			*Add_pu16ADCValue = (ADCL>>6);
			Loc_u16Result = ADCH;
			*Add_pu16ADCValue |= (Loc_u16Result<<2);
		#else
			Loc_u8State = ADC_enuNotOk;
			 
		#endif
		SET_BIT(ADCSRA,ADIF);
		  
	}
	else
	{
		Loc_u8State = ADC_enuNotOk;
	}
	
	
	return Loc_u8State;
	
}



ADC_tenuErrorStatus ADC_enuASynchGetADCValue( u16 * Add_pu16ADCValue)
{
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOk;
	ADD_pu16ADCValue = Add_pu16ADCValue;
	
	//SET_BIT(ADCSRA,ADIF);
	ADC_enuEnableInterrupt();
	/*Start Conversion*/
	SET_BIT(ADCSRA,ADSC);
	return Loc_u8State;
	
}

ADC_tenuErrorStatus ADC_enuEnableInterrupt(void)
{
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOk;
	SET_BIT(ADCSRA,ADIE);
	return Loc_u8State;
}

ADC_tenuErrorStatus ADC_enuDisableInterrupt(void)
{
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOk;
	CLR_BIT(ADCSRA,ADIE);
	return Loc_u8State;
}


ADC_tenuErrorStatus ADC_enuSetCallback(void(*CpyFuncPtr)(void))
{
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOk;
	if(CpyFuncPtr != NULL)
	{
		CallbackPtr_EOJ = CpyFuncPtr;
	}
	else
	{
		Loc_u8State = ADC_enuNullPtr;
	}
	
	return Loc_u8State;
}

ISR_ADC(16)
{

	if(CallbackPtr_EOJ != NULL)
	{
		if(ADD_pu16ADCValue != NULL)
		{
			u16 Loc_u16Result = 0;
			#if (ADC_Adjustment == ADC_Right)
			*ADD_pu16ADCValue = ADCL;
			Loc_u16Result = ADCH;
			*ADD_pu16ADCValue |= (Loc_u16Result<<8);
			#elif (ADC_Adjustment == ADC_Left)
			*ADD_pu16ADCValue = (ADCL>>6);
			Loc_u16Result = ADCH;
			*ADD_pu16ADCValue |= (Loc_u16Result<<2);
			#else
			#endif
			SET_BIT(ADCSRA,ADIF);
		CallbackPtr_EOJ();
		}
		else
		{
		}
	}
	else
	{
	}
}
