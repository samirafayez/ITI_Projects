/*
 * Systick_Cfg.c
 *
 *  Created on: Mar 25, 2023
 *      Author: HP
 */


#include "03_Systick/Systick_Cfg.h"


const Systick_tstrCFG Systick_strcfg =
{
.Systick_enuClkSrc = Systick_EXT_Clk,
.Systick_Load = 16777215
};
