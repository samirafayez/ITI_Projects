/*
 * UltraSonic.c
 *
 * Created: 3/15/2023 5:02:45 AM
 *  Author: HP
 */ 
#define F_CPU 1000000UL
#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "UltraSonic.h"
#include "UltraSonic_Cfg.h"
#include "UltraSonic_prv.h"
#include "../../00_MCAL/05_TMR1/TMR1.h"
#include "../../00_MCAL/00_DIO/DIO.h"
#include <util/delay.h>

static volatile u8 NumberofOFs = 0;
static volatile u16 ICR_temp = 0;
static volatile u16 Distance = 0;

void ICU_ISR(void)
{
	f32 Time = 0.0;
	f32 Time1 = 0.0;
	f32 Time2 = 0.0;
	u16 ICRValue =0;
	static u8 Falling_flag =0;

	if(Falling_flag == 0)
	{
		NumberofOFs=0;
		TMR1_enuFallingEdgeSel();
		Falling_flag=1;
		TMR1_enuSetTCNT1(0);
	}
	else
	{
		TMR1_enuReadICR(&ICRValue);
		TMR1_enuCalculate_Time(ICRValue,&Time1);
		TMR1_enuCalculate_Time(65535,&Time2);
		//Time = ICRValue + 65535*NumberofOFs;
		Time = Time1 + (NumberofOFs*Time2);
		Distance = (f32)Time/(580*2);
		TMR1_enuRisingEdgeSel();
		Falling_flag = 0;
	}

}

void OF_ISR(void)
{
	NumberofOFs++;
}

UltraSonic_tenuErrorStatus UltraSonic_enuInit(void)
{
	UltraSonic_tenuErrorStatus Loc_u8State = UltraSonic_enuOK;
	TMR1_enuRisingEdgeSel();
	TMR1_ICUInterruptEnable();
	TMR1_OFInterruptEnable();
	TMR1_enuRegisterCallback(TMR1_enuInputCapture,ICU_ISR);
	TMR1_enuRegisterCallback(TMR1_enuOverflow,OF_ISR);
	
	return Loc_u8State;
}

UltraSonic_tenuErrorStatus UltraSonic_enuReadDistance(u16 * Cpy_u16Distance)
{
	UltraSonic_tenuErrorStatus Loc_u8State = UltraSonic_enuOK;
	if(Cpy_u16Distance != NULL)
	{
		DIO_enuSetPin(UltraSonic_TriggerPin);
		_delay_us(10);
		DIO_enuClearPin(UltraSonic_TriggerPin);
		while(Distance == 0);
		*Cpy_u16Distance = Distance;
	}
	else
	{
		Loc_u8State = UltraSonic_enuNullPtr;
	}
	
	return Loc_u8State;
}