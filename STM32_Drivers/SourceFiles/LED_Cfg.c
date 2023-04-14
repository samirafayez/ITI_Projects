/*
 * LED_Cfg.c
 *
 *  Created on: Feb 23, 2023
 *      Author: HP
 */


#include "00_LED/LED.h"
#include "00_LED/LED_Cfg.h"



const LED_tstrLEDcfg LED_strLEDcfg[LED_enuNumberOfLEDs] =
{

[LED_enuALARM] = {LED_ACTIVE_HIGH,LED_PORTB,LED_enuPin4,LED_SPEED_HIGH}


};
