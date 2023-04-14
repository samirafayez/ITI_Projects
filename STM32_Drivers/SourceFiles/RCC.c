/*
 * RCC.c
 *
 *  Created on: Feb 4, 2023
 *      Author: HP
 */
#include "std_defines.h"
#include "bit_math.h"
#include "00_RCC/RCC.h"
#include "00_RCC/RCC_prv.h"
#include "00_RCC/RCC_Cfg.h"










RCC_tenuErrorStatus RCC_ConfigSysClk(RCC_tenuClkValues Cpy_u8ClkValue)
{

	u8 Loc_u8State = RCC_enuOK;
	//check first if pll is disabled
	CLR_BIT(RCC_CR, PLL_ON);
	while(!(RCC_CR>>PLL_RDY)&1);

	if(Cpy_u8ClkValue<RCC_ClkNumbers)
	{
		if(PLL_Src_Clk == HSI )
		{
			RCC_SwitchSysClk(RCC_HSI);
			RCC_PLLCFGR |= (HSI<<PLL_SRC);
			RCC_PLLCFGR |= 16;
			RCC_PLLCFGR |= (168<<PLLN);
			RCC_PLLCFGR |= ((Cpy_u8ClkValue*2)<<PLLP);
		}
		else if(PLL_Src_Clk == HSE)
		{
			RCC_SwitchSysClk(RCC_HSE);
			RCC_PLLCFGR |= (HSE<<PLL_SRC);
			RCC_PLLCFGR |= 8;
			RCC_PLLCFGR |= (168<<PLLN);
			RCC_PLLCFGR |= ((Cpy_u8ClkValue*2)<<PLLP);
		}
		RCC_SwitchSysClk(RCC_PLL);

	}
	else
	{
		Loc_u8State = RCC_enuNotOK;
	}
	return Loc_u8State;
}



RCC_tenuErrorStatus RCC_SwitchSysClk(RCC_SystemClk Cpy_u8SysClk)
{
	u8 Loc_u8State = RCC_enuOK;
	if (Cpy_u8SysClk == RCC_HSE)
		{
			SET_BIT(RCC_CR, HSE_ON);
			while((RCC_CR>>HSE_RDY)&1);
			SET_BIT(RCC_CFGR, SW0); //Select HSE as system clock.
			CLR_BIT(RCC_CFGR, SW1);
			while(((RCC_CFGR>>SWS0)&1) && !((RCC_CFGR>>SWS1)&1));

		}
		else if(Cpy_u8SysClk == RCC_HSI)
		{
			SET_BIT(RCC_CR, HSI_ON);
			while((RCC_CR>>HSI_RDY)&1);
			CLR_BIT(RCC_CFGR, SW0); //Select HSI as system clock.
			CLR_BIT(RCC_CFGR, SW1);
			while(!((RCC_CFGR>>SWS0)&1) && !((RCC_CFGR>>SWS1)&1));

		}
		else if(Cpy_u8SysClk == RCC_PLL)
		{
			SET_BIT(RCC_CR, PLL_ON);
			while((RCC_CR>>PLL_RDY)&1);
			CLR_BIT(RCC_CFGR, SW0); //Select PLL as system clock.
			SET_BIT(RCC_CFGR, SW1);
			while(!((RCC_CFGR>>SWS0)&1) && ((RCC_CFGR>>SWS1)&1));

		}
		else
		{
			Loc_u8State = RCC_enuNotOK;
		}
	return Loc_u8State;
}




RCC_tenuErrorStatus RCC_Peripheral_EnableSysClk(RCC_Buses Cpy_u8Bus, RCC_Peripherals Cpy_u8Peripheral)
{
	u8 Loc_u8State = RCC_enuOK;
	switch(Cpy_u8Bus)
	{
		case 0:
			SET_BIT(RCC_AHB1ENR, Cpy_u8Peripheral);
			break;
		case 1:
			SET_BIT(RCC_AHB2ENR, Cpy_u8Peripheral);
			break;
		case 2:
			SET_BIT(RCC_APB1ENR, Cpy_u8Peripheral);
			break;
		case 3:
			SET_BIT(RCC_APB2ENR, Cpy_u8Peripheral);
			break;
	}


	return Loc_u8State;
}


RCC_tenuErrorStatus RCC_Peripheral_DisableSysClk(RCC_Buses Cpy_u8Bus, RCC_Peripherals Cpy_u8Peripheral)
{
	u8 Loc_u8State = RCC_enuOK;
	switch(Cpy_u8Bus)
	{
		case 0:
			CLR_BIT(RCC_AHB1ENR, Cpy_u8Peripheral);
			break;
		case 1:
			CLR_BIT(RCC_AHB2ENR, Cpy_u8Peripheral);
			break;
		case 2:
			CLR_BIT(RCC_APB1ENR, Cpy_u8Peripheral);
			break;
		case 3:
			CLR_BIT(RCC_APB2ENR, Cpy_u8Peripheral);
			break;
	}


	return Loc_u8State;
}


