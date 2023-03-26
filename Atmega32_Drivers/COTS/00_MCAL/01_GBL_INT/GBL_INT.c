/*
 * GBL_INT.c
 *
 * Created: 2/1/2023 3:09:06 PM
 *  Author: HP
 */ 


#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "GBL_INT.h"
#include "GBL_INT_Cfg.h"
#include "GBL_INT_piv.h"



GBL_INT_tenuErrorStatus INT_GlobalEnable(void)
{
	GBL_INT_tenuErrorStatus Loc_u8State = GBL_INT_enuOK;
	SET_BIT(SREG,7);
	return Loc_u8State;
}


GBL_INT_tenuErrorStatus INT_GlobalDisable(void)
{
	GBL_INT_tenuErrorStatus Loc_u8State = GBL_INT_enuOK;
	CLR_BIT(SREG,7);
	return Loc_u8State;
}
