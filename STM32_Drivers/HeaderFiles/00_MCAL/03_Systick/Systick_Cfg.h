/*
 * Systick_Cfg.h
 *
 *  Created on: Mar 25, 2023
 *      Author: HP
 */

#ifndef SYSTICK_CFG_H_
#define SYSTICK_CFG_H_


#include "std_defines.h"

#define CLK_FREQUENCY 25000000UL


typedef enum
{
	Systick_EXT_Clk=0,
	Systick_EXTClkDividedBy8

}Systick_tenuClkSrc;


typedef struct
{
	Systick_tenuClkSrc Systick_enuClkSrc;
	u32 Systick_Load;
}Systick_tstrCFG;



#endif /* SYSTICK_CFG_H_ */
