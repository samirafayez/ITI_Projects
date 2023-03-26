/*
 * UltraSonic.h
 *
 * Created: 3/15/2023 5:03:07 AM
 *  Author: HP
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

typedef enum{

	UltraSonic_enuOK = 0,
	UltraSonic_enuNotOK ,
	UltraSonic_enuNullPtr

}UltraSonic_tenuErrorStatus;


UltraSonic_tenuErrorStatus UltraSonic_enuReadDistance(u16 * Cpy_u16Distance);
UltraSonic_tenuErrorStatus UltraSonic_enuInit(void);
void ICU_ISR(void);
void OF_ISR(void);


#endif /* ULTRASONIC_H_ */