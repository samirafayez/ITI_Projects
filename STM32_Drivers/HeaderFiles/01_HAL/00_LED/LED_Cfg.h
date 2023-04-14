/*
 * LED_Cfg.h
 *
 *  Created on: Feb 23, 2023
 *      Author: HP
 */

#ifndef LED_CFG_H_
#define LED_CFG_H_


#include "std_defines.h"




typedef enum {
LED_enuALARM=0,
LED_enuRED,
LED_enuTOGGLE,
LED_enuNumberOfLEDs

}LED_tenuLEDNames;





typedef struct {
u8 LED_Mode;
u8 LED_PORT;
u8 LED_PIN;
u8 LED_SPEED;
}LED_tstrLEDcfg;










#endif /* LED_CFG_H_ */
