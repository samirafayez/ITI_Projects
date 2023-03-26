/*
 * TMR0.h
 *
 * Created: 3/12/2023 12:10:13 AM
 *  Author: HP
 */ 


#ifndef TMR1_H_
#define TMR1_H_

#include "TMR1_Cfg.h"



typedef enum{
	TMR1_enuOK = 0,
	TMR1_enuNotOK,
	TMR1_enuNullPtr
}TMR1_tenuErrorStatus;


typedef enum{
	TMR1_enuInputCapture=0,
	TMR1_enuOverflow,
	TMR1_enuCompareOutA
}TMR1tenucbf_t;



#define TMR1_FallingEdge       0
#define TMR1_RisingEdge        1

#define TMR1_NoClkSrc          0
#define TMR1_NoPrescaling      1
#define TMR1_Prescaler_8       2
#define TMR1_Prescaler_64      3
#define TMR1_Prescaler_256     4
#define TMR1_Prescaler_1024    5
#define TMR1_ExternalClk_FE    6
#define TMR1_ExternalClk_RE    7

#define TMR1_Normal                         0
#define TMR1_PWM_PhaseCorrect_8bit          1
#define TMR1_PWM_PhaseCorrect_9bit          2
#define	TMR1_PWM_PhaseCorrect_10bit			3
#define	TMR1_CTC_OCR						4
#define	TMR1_Fast_PWM_8bit					5
#define	TMR1_Fast_PWM_9bit					6
#define	TMR1_Fast_PWM_10bit					7
#define	TMR1_PWM_PhaseFrequency_Correct_ICR	8
#define	TMR1_PWM_PhaseFrequency_Correct_OCR	9
#define	TMR1_PWM_PhaseCorrect_ICR			10
#define	TMR1_PWM_PhaseCorrect_OCR			11
#define	TMR1_CTC_ICR						12
#define	TMR1_Fast_PWM_ICR					14
#define	TMR1_Fast_PWM_OCR					15

/* WAVEFORM of normal and CTC mode:*/
#define CTC_OC1_NormalMode                  0
#define CTC_OC1_TOGGLE                      1
#define CTC_OC1_CLEAR                       2
#define CTC_OC1_SET                         3
/* WAVEFORM of fast PWM:*/
#define FastPWM_OC1_NormalMode              0
#define FastPWM_OC1A_Toggle                 1
#define FastPWM_OC1_NONINVERTING            2
#define FastPWM_OC1_INVERTING               3
/* WAVEFORM of phase correct PWM:*/
#define PhaseCorrect_OC1_NormalMode         0
#define PhaseCorrect_OC1A_Toggle            1
#define PhaseCorrect_OC1_CLEARONUPCOUNT     2
#define PhaseCorrect_OC1_SETONUPCOUNT       3




TMR1_tenuErrorStatus TMR1_vidInit(void);
TMR1_tenuErrorStatus TMR1_enuSetTickTimeMS(u16 Copy_u16TickTime, u32 Copy_u32Clock);
TMR1_tenuErrorStatus TMR1_enuRegisterCallback(TMR1tenucbf_t Cpy_enucbf,void(*CpyFuncPtr)(void));
TMR1_tenuErrorStatus TMR1_enuStart(void);
TMR1_tenuErrorStatus TMR1_ICUInterruptEnable(void);
TMR1_tenuErrorStatus TMR1_ICUInterruptDisable(void);
TMR1_tenuErrorStatus TMR1_OFInterruptEnable(void);
TMR1_tenuErrorStatus TMR1_OCAInterruptEnable(void);
TMR1_tenuErrorStatus TMR1_OFInterruptDisable(void);
TMR1_tenuErrorStatus TMR1_enuReadICR(u16 * Add_pu16ICRValue);
TMR1_tenuErrorStatus TMR1_enuSetTCNT1(u16 Cpy_u16TCNT1Value);
TMR1_tenuErrorStatus TMR1_enuSetICR1(u16 Cpy_u16ICRValue);
TMR1_tenuErrorStatus TMR1_enuSetDutyCycle(f32 Cpy_f32DutyCycle);
TMR1_tenuErrorStatus TMR1_SetCompareMatchOCA(u16 Cpy_u8CompareMatchVal);
TMR1_tenuErrorStatus TMR1_enuRisingEdgeSel(void);
TMR1_tenuErrorStatus TMR1_enuFallingEdgeSel(void);
TMR1_tenuErrorStatus TMR1_enuCalculate_Time( u16 Cpy_ICRValue, f32 * Add_f32Time);

#endif /* TMR1_H_ */