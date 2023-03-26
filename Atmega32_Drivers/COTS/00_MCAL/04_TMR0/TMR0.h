/*
 * TMR0.h
 *
 * Created: 2/27/2023 3:21:08 AM
 *  Author: HP
 */ 


#ifndef TMR0_H_
#define TMR0_H_


typedef enum{
TMR0_enuOK = 0,
TMR0_enuNotOK,
TMR0_enuNullPtr
}TMR0_enuErrorStatus;

typedef enum{
TMR0_enuOutCompare=0,
TMR0_enuOverflow
}TMR0tenucbf_t;


TMR0_enuErrorStatus TMR0_vidInitPreCompile(void);
TMR0_enuErrorStatus TMR0_vidInitPostCompile(void);
TMR0_enuErrorStatus TMR0_enuSetTickTimeMS(u16 Copy_u16TickTime, u32 Copy_u32Clock);
TMR0_enuErrorStatus TMR0_enuStart(void);
TMR0_enuErrorStatus TMR0_enuRegisterCallback(TMR0tenucbf_t Cpy_enucbf,void(*CpyFuncPtr)(void));
TMR0_enuErrorStatus TMR0_OCInterruptEnable(void);
TMR0_enuErrorStatus TMR0_OVInterruptEnable(void);
TMR0_enuErrorStatus TMR0_ForceCompareEN(void);
TMR0_enuErrorStatus TMR0_ForceCompareDIS(void);
TMR0_enuErrorStatus TMR0_SetCompareMatch(u8 Cpy_u8CompareMatchVal);
TMR0_enuErrorStatus TMR0_enuSetDutyCycle(f32 Cpy_f32DutyCycle);




#endif /* TMR0_H_ */