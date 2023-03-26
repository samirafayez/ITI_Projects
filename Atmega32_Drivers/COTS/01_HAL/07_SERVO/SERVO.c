/*
 * SERVO.c
 *
 * Created: 3/11/2023 9:10:09 AM
 *  Author: HP
 */ 
#define  F_CPU 1000000U
#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "SERVO.h"
#include "SERVO_Cfg.h"
#include "SERVO_prv.h"
#include "../../00_MCAL/05_TMR1/TMR1.h"

SERVO_tenuErrorStatus SERVO_enuWriteAngle(u8 Cpy_u8AngleValue)
{
	SERVO_tenuErrorStatus Loc_u8State = SERVO_enuOK;
	f32 Loc_f32DutyCycleValue = 0;
	u16 Loc_u16TOPValue = 0;
	switch(TMR1_Prescaler)
	{
		case TMR1_NoPrescaling:
			Loc_u16TOPValue = (F_CPU/50)-1;
			break;
		case TMR1_Prescaler_8:
			Loc_u16TOPValue = (F_CPU/(50*8))-1;
			break;
		case TMR1_Prescaler_64:
			Loc_u16TOPValue = (F_CPU/(50*64))-1;
			break;
		case TMR1_Prescaler_256:
			Loc_u16TOPValue = (F_CPU/(50*256))-1;
			break;
		case TMR1_Prescaler_1024:
			Loc_u16TOPValue = (F_CPU/(50*1024))-1;
			break;
		default:
			Loc_u8State = SERVO_enuNotOK;
			break;
	}
	
	TMR1_enuSetICR1(Loc_u16TOPValue);
	

	if(Cpy_u8AngleValue >=0 && Cpy_u8AngleValue < 90)
	{
		Loc_f32DutyCycleValue = Cpy_u8AngleValue*((0.075-0.05)/90.0) + 0.05;
		TMR1_enuSetDutyCycle(Loc_f32DutyCycleValue);
		
	}
	else if(Cpy_u8AngleValue >= 90 && Cpy_u8AngleValue <= 180)
	{
		Loc_f32DutyCycleValue = (Cpy_u8AngleValue-90)*((0.1-0.075)/90.0) + 0.075;
		TMR1_enuSetDutyCycle(Loc_f32DutyCycleValue);
	}
	else
	{
		Loc_u8State = SERVO_enuNotOK;
	}
	
	return Loc_u8State;
	
}