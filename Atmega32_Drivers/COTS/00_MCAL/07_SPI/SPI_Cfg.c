/*
 * SPI_Cfg.c
 *
 * Created: 4/4/2023 3:05:23 PM
 *  Author: HP
 */ 

#include "../../LIB/std_defines.h"
#include "SPI.h"
#include "SPI_Cfg.h"



const SPI_tstrCfg SPI_strCfg = 
{
	.SPI_enuSPIDataOrder = SPI_enuLSBFirst,
	.SPI_enuMasterSlaveSel = SPI_enuMaster,
	.SPI_enuClkPolarity = SPI_enuIdleOne,
	.SPI_enuClkPhase = SPI_enuSampleFirst,
	.SPI_enuClkRatePre = SPI_enuClk_128
	
};