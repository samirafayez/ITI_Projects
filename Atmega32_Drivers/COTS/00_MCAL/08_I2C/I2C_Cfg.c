/*
 * I2C_Cfg.c
 *
 * Created: 4/16/2023 8:27:40 PM
 *  Author: HP
 */ 

#include "../../LIB/std_defines.h"
#include "I2C_Cfg.h"




const I2C_tstrCFG_t I2C_strCFG = 
{
	.I2C_BitRate = 2,
	.I2C_Prescaler = 0,
	.I2C_SlaveAddress = 64,
	.I2C_InterruptEN = I2C_enuDisabled,
	.GeneralCallRecognitionEN = I2C_enuDisabled,
	.I2C_AcknowledgeEN = I2C_enuEnabled
	
};