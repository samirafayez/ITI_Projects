/*
 * ADC.c
 *
 *  Created on: Apr 14, 2023
 *      Author: HP
 */

#include "std_defines.h"
#include "bit_math.h"
#include "06_ADC/ADC.h"
#include "06_ADC/ADC_Cfg.h"
#include "06_ADC/ADC_prv.h"
#include "00_RCC/RCC.h"
#include "02_NVIC/NVIC.h"

extern const ADC_tstrCfg ADC_strCfg;



ADC_tenuErrorStatus ADC_enuInit(void)
{
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOK;
	ADC_REG->ADC_CR1 = 0;
	ADC_REG->ADC_CR2 = 0;

	//Enabling ADC and Selecting Conversion Type
	if((ADC_strCfg.ADC_tenuADCEN < 2) && (ADC_strCfg.ADC_enuConversionType < 2))
	{
		RCC_Peripheral_EnableSysClk(APB2, ADC1);
		NVIC_enuEnable(NVIC_ADC_1_2);
		ADC_REG->ADC_CR2 |= (ADC_strCfg.ADC_tenuADCEN << ADON) | (ADC_strCfg.ADC_enuConversionType << CONT);
	}
	else
	{
		Loc_u8State = ADC_enuNotOK;
	}

	//Enabling Scan Mode and Setting Resolution
	if((ADC_strCfg.ADC_enuScanMode < 2) && (ADC_strCfg.ADC_enuResolution < 4))
	{
		ADC_REG->ADC_CR1 |= (ADC_strCfg.ADC_enuScanMode << SCAN) | (ADC_strCfg.ADC_enuResolution << 24);
	}
	else
	{
		Loc_u8State = ADC_enuNotOK;
	}


	if((ADC_strCfg.ADC_tstrInterrupt.ADC_enuEOCFlagEN < 2) && (ADC_strCfg.ADC_tstrInterrupt.ADC_enuJEOCFlagEN < 2) && (ADC_strCfg.ADC_tstrInterrupt.ADC_enuEOCEN < 2))
	{
		ADC_REG->ADC_CR1 |= (ADC_strCfg.ADC_tstrInterrupt.ADC_enuEOCFlagEN << EOCIE) | (ADC_strCfg.ADC_tstrInterrupt.ADC_enuJEOCFlagEN << JEOCIE);
		ADC_REG->ADC_CR2 |= (ADC_strCfg.ADC_tstrInterrupt.ADC_enuEOCEN << EOCS);
	}
	else
	{
		Loc_u8State = ADC_enuNotOK;
	}

	if((ADC_strCfg.ADC_enuAWDEnable < 2) && (ADC_strCfg.ADC_enuJAWDEnable < 2))
	{
		ADC_REG->ADC_CR1 |= (ADC_strCfg.ADC_enuAWDEnable << AWDEN) | (ADC_strCfg.ADC_enuJAWDEnable << JAWDEN);
	}
	else
	{
		Loc_u8State = ADC_enuNotOK;
	}
	//Discontinuous Mode
	if( (ADC_strCfg.ADC_enuDiscontModeRegChannelsEN < 2) && (ADC_strCfg.ADC_enuDiscontModeInjChannelsEN < 2))
	{
		if(ADC_strCfg.ADC_enuDiscontModeRegChannelsEN == ADC_enuEnabled)
		{
			SET_BIT(ADC_REG->ADC_CR1, DISCEN);
			ADC_REG->ADC_CR1 |= (ADC_strCfg.ADC_u8DiscModeChannelCount << 13);
		}

		ADC_REG->ADC_CR1 |= (ADC_strCfg.ADC_enuDiscontModeInjChannelsEN << JDISCEN);
	}
	else
	{
		Loc_u8State = ADC_enuNotOK;
	}

	if(ADC_strCfg.ADC_enuJAUTOEN < 2)
	{
		ADC_REG->ADC_CR1 |= (ADC_strCfg.ADC_enuJAUTOEN << JAUTO);
	}
	else
	{
		Loc_u8State = ADC_enuNotOK;
	}

	if((ADC_strCfg.ADC_enuAWatchdogChannelEN < 2) && (ADC_strCfg.ADC_u8AWatchdogChannelSel < 19))
	{
		ADC_REG->ADC_CR1 |= (ADC_strCfg.ADC_enuAWatchdogChannelEN << AWDSGL) | (ADC_strCfg.ADC_u8AWatchdogChannelSel);
	}
	else
	{
		Loc_u8State = ADC_enuNotOK;
	}

	if((ADC_strCfg.ADC_enuEXTRegularChannels < 4) && (ADC_strCfg.ADC_enuEXTInjectedChannels < 4))
	{
		if((ADC_strCfg.ADC_enuRegEXTTrigger_Sel < 16) && (ADC_strCfg.ADC_enuInjEXTTrigger_Sel < 16))
		{
			ADC_REG->ADC_CR2 |= (ADC_strCfg.ADC_enuEXTRegularChannels << 28) | (ADC_strCfg.ADC_enuEXTInjectedChannels << 20) |
					(ADC_strCfg.ADC_enuRegEXTTrigger_Sel << 24) | (ADC_strCfg.ADC_enuInjEXTTrigger_Sel << 16);
		}
		else
		{
			Loc_u8State = ADC_enuNotOK;
		}

	}
	else
	{
		Loc_u8State = ADC_enuNotOK;
	}

	//Setting Thresholds

	ASSIGN_REG(ADC_REG->ADC_HTR, ADC_strCfg.ADC_u16HigherThreshold);
	ASSIGN_REG(ADC_REG->ADC_LTR, ADC_strCfg.ADC_u16LowerThreshold);

	return Loc_u8State;
}


ADC_tenuErrorStatus ADC_enuStartConversion_RegularChannels(u16 * Cpy_pu16ADCValue)
{
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOK;
	SET_BIT(ADC_REG->ADC_CR2, SWSTART);
	while(!GET_BIT(ADC_REG->ADC_SR, EOC));
	* Cpy_pu16ADCValue = ADC_REG->ADC_DR;


	return Loc_u8State;
}


ADC_tenuErrorStatus ADC_enuStartConversion_InjectedChannels(ADC_tenuInjectedChannels ADC_enuInjectedChannels, u16 * Cpy_pu16ADCValue)
{
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOK;
	SET_BIT(ADC_REG->ADC_CR2, JSWSTART);
	while(!GET_BIT(ADC_REG->ADC_SR, EOC));
	* Cpy_pu16ADCValue = ADC_REG->ADC_JDR[ADC_enuInjectedChannels];

	return Loc_u8State;
}


ADC_tenuErrorStatus ADC_enuEnableDMA(void)
{
	ADC_tenuErrorStatus Loc_u8State = ADC_enuOK;
	SET_BIT(ADC_REG->ADC_CR2, 8);

	return Loc_u8State;

}
