/*
 * TMR0_Cfg.c
 *
 * Created: 2/27/2023 3:28:43 AM
 *  Author: HP
 */ 

#include "TMR0_Cfg.h"


/************************************************************************/
/*                        PostCompile Configuration                     */
/************************************************************************/
const TMR0Config_t TMR0_strCfg =
{
.TMR0_MODE = TMR0_enuNormal,
.TMR0_PRESCALER = TMR0_enuPrescalerCLK_64,
.TMR0_WAVEFORM = OC0_enuNORMAL,
.TMR0_PRELOADVALUE = 0
};



