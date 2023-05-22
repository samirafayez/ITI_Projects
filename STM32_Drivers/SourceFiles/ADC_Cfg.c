/*
 * ADC_Cfg.c
 *
 *  Created on: Apr 14, 2023
 *      Author: HP
 */


#include "std_defines.h"
#include "06_ADC/ADC_Cfg.h"




const ADC_tstrCfg ADC_strCfg =
{
		.ADC_tenuADCEN = ADC_enuDisabled,
		.ADC_enuConversionType = ADC_enuSingleConversion,
		.ADC_enuScanMode = ADC_enuDisabled,
		.ADC_enuResolution = ADC_enu8Bit,
		.ADC_enuAWDEnable = ADC_enuDisabled,
		.ADC_enuJAWDEnable = ADC_enuDisabled,
		.ADC_u16HigherThreshold = 4000,
		.ADC_u16LowerThreshold = 0,
		.ADC_enuDiscontModeRegChannelsEN = ADC_enuDisabled,
		.ADC_enuDiscontModeInjChannelsEN = ADC_enuDisabled,
		.ADC_u8DiscModeChannelCount = 1,
		.ADC_enuJAUTOEN = ADC_enuDisabled,
		.ADC_enuAWatchdogChannelEN = ADC_enuDisabled,
		.ADC_u8AWatchdogChannelSel = 1,
		.ADC_enuEXTRegularChannels = ADC_enuEXTDisabled,
		.ADC_enuEXTInjectedChannels = ADC_enuEXTDisabled,
		.ADC_enuRegEXTTrigger_Sel = ADC_enuTMR1CC1,
		.ADC_enuInjEXTTrigger_Sel = ADC_enuTMR1CC4,

		.ADC_tstrInterrupt = {
				.ADC_enuEOCFlagEN = ADC_enuEnabled,
				.ADC_enuJEOCFlagEN = ADC_enuEnabled,
				.ADC_enuEOCEN = ADC_enuEnabled

		}

};
