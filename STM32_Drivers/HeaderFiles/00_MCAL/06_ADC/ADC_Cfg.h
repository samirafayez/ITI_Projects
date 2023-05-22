/*
 * ADC_Cfg.h
 *
 *  Created on: Apr 14, 2023
 *      Author: HP
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_



typedef enum
{
	ADC_enu6Bit=0,
	ADC_enu8Bit,
	ADC_enu10Bit,
	ADC_enu12Bit
}ADC_tenuResolution;



typedef enum
{
	ADC_enuSingleConversion=0,
	ADC_enuContConversion
}ADC_tenuConversionType;


typedef enum
{
	ADC_enuEXTDisabled=0,
	ADC_enuEXTRisingEdge,
	ADC_enuEXTFallingEdge,
	ADC_enuEXTBothEdges

}ADC_tenuEXTTrigger;


typedef enum
{
	ADC_enuTMR1CC1=0,
	ADC_enuTMR1CC2,
	ADC_enuTMR1CC3,
	ADC_enuTMR2CC2,
	ADC_enuTMR2CC3,
	ADC_enuTMR2CC4,
	ADC_enuTMR2TRGO,
	ADC_enuTMR3CC1,
	ADC_enuTMR3TRGO,
	ADC_enuTMR4CC4,
	ADC_enuTMR5CC1,
	ADC_enuTMR5CC2,
	ADC_enuTMR5CC3,
	ADC_enuTMR8CC1,
	ADC_enuTMR8TRGO,
	ADC_enuEXTILine11

}ADC_tenuRegEXTTrigger_Sel;


typedef enum
{
	ADC_enuTMR1CC4=0,
	ADC_enuTMR1TRGO,
	ADC_enuTMR2CC1,
	ADC_enuINJTMR2TRGO,
	ADC_enuTMR3CC2,
	ADC_enuTMR3CC4,
	ADC_enuTMR4CC1,
	ADC_enuTMR4CC2,
	ADC_enuTMR4CC3,
	ADC_enuTMR4TRGO,
	ADC_enuTMR5CC4,
	ADC_enuTMR5TRGO,
	ADC_enuTMR8CC2,
	ADC_enuTMR8CC3,
	ADC_enuTMR8CC4,
	ADC_enuEXTILine15

}ADC_tenuInjEXTTrigger_Sel;






typedef enum
{
	ADC_enuDisabled=0,
	ADC_enuEnabled

}ADC_tenuEN;


typedef struct{
	ADC_tenuEN ADC_tenuADCEN;
	ADC_tenuConversionType ADC_enuConversionType;
	ADC_tenuEN ADC_enuScanMode;
	ADC_tenuResolution ADC_enuResolution;
	ADC_tenuEN ADC_enuAWDEnable;
	ADC_tenuEN ADC_enuJAWDEnable;
	u16 ADC_u16HigherThreshold : 12;
	u16 ADC_u16LowerThreshold : 12;
	ADC_tenuEN ADC_enuDiscontModeRegChannelsEN;
	ADC_tenuEN ADC_enuDiscontModeInjChannelsEN;
	u8 ADC_u8DiscModeChannelCount : 3;  //no. of channels at every conversion
	ADC_tenuEN ADC_enuJAUTOEN;   //trigger channel after every regular one
	ADC_tenuEN ADC_enuAWatchdogChannelEN;
	u8 ADC_u8AWatchdogChannelSel : 5; //0-18 Channels
	ADC_tenuEXTTrigger ADC_enuEXTRegularChannels;
	ADC_tenuEXTTrigger ADC_enuEXTInjectedChannels;
	ADC_tenuRegEXTTrigger_Sel ADC_enuRegEXTTrigger_Sel;
	ADC_tenuInjEXTTrigger_Sel ADC_enuInjEXTTrigger_Sel;

	struct
	{
		ADC_tenuEN ADC_enuEOCFlagEN;
		ADC_tenuEN ADC_enuJEOCFlagEN;
		ADC_tenuEN ADC_enuEOCEN;

	}ADC_tstrInterrupt;


}ADC_tstrCfg;


#endif /* ADC_CFG_H_ */
