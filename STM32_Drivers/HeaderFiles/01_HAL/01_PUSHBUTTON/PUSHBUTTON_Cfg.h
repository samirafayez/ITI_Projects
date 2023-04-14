/*
 * PUSHBUTTON_Cfg.h
 *
 *  Created on: Feb 24, 2023
 *      Author: HP
 */

#ifndef PUSHBUTTON_CFG_H_
#define PUSHBUTTON_CFG_H_

#include "std_defines.h"



typedef struct
{

u8 PUSHBUTTON_MODE;
u8 PUSHBUTTON_PORT;
u8 PUSHBUTTON_PIN;
u8 PUSHBUTTON_SPEED;

}PUSHBUTTON_tstrPUSHBUTTONcfg;


typedef enum {
PUSHBUTTON_enuSwitch=0,
PUSHBUTTON_enuNumberOfPUSHBUTTONs

}PUSHBUTTON_tenuPUSHBUTTONNames;


#endif /* PUSHBUTTON_CFG_H_ */
