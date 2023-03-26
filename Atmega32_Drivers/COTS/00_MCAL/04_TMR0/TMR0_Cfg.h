/*
 * TMR0_Cfg.h
 *
 * Created: 2/27/2023 3:22:03 AM
 *  Author: HP
 */ 


#ifndef TMR0_CFG_H_
#define TMR0_CFG_H_

#include "../../LIB/std_defines.h"



/************************************************************************/
/*                        PreCompile Configuration                      */
/************************************************************************/
/*TMR0_Mode:
* TMR0_Normal
* TMR0_CTC
* TMR0_FASTPWM
* TMR0_PHASECORRECTPWM
*/
/*TMR0_Prescaler:
* TMR0_NoPrescaling
* TMR0_PrescalerCLK_8
* TMR0_PrescalerCLK_64
* TMR0_PrescalerCLK_256
* TMR0_PrescalerCLK_1024
* TMR0_ExtCLKSrc_FE
* TMR0_ExtCLKSrc_RE
*/
/*
* WAVEFORM of normal and CTC mode:
* OC0_NORMAL
* OC0_TOGGLE
* OC0_CLEAR
* OC0_SET
*/
/*
* WAVEFORM of fast PWM:
* OC0_NORMAL
* OC0_NONINVERTING
* OC0_INVERTING
*/
/*
* WAVEFORM of phase correct PWM:
*OC0_CLEARONUPCOUNT
*OC0_SETONUPCOUNT
*/

#define TMR0_Mode TMR0_Normal
#define WAVEFORM OC0_NORMAL
#define TMR0_Prescaler TMR0_enuPrescalerCLK_64



typedef enum{
TMR0_enuNoClkSrc=0,    
TMR0_enuNoPrescaling, 
TMR0_enuPrescalerCLK_8, 
TMR0_enuPrescalerCLK_64, 
TMR0_enuPrescalerCLK_256,
TMR0_enuPrescalerCLK_1024,
TMR0_enuExtCLKSrc_FE,      
TMR0_enuExtCLKSrc_RE     

}TMR0_tenuPrescaler;


typedef enum{
TMR0_enuNormal=0,
TMR0_enuCTC,
TMR0_enuFASTPWM,
TMR0_enuPHASECORRECTPWM
}TMR0_tenuMode;


typedef enum{
OC0_enuNORMAL=0,
OC0_enuTOGGLE,
OC0_enuCLEAR,
OC0_enuSET,   
OC0_enuNONINVERTING=2,
OC0_enuINVERTING ,
OC0_enuCLEARONUPCOUNT =2,
OC0_enuSETONUPCOUNT
}TMR0_tenuWaveform;


typedef struct
{
TMR0_tenuMode TMR0_MODE;
TMR0_tenuPrescaler TMR0_PRESCALER;
TMR0_tenuWaveform TMR0_WAVEFORM;
u8 TMR0_PRELOADVALUE;
}TMR0Config_t;


#endif /* TMR0_CFG_H_ */