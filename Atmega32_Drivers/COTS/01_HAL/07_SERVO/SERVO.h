/*
 * SERVO.h
 *
 * Created: 3/11/2023 9:09:25 AM
 *  Author: HP
 */ 


#ifndef SERVO_H_
#define SERVO_H_


typedef enum{

SERVO_enuOK = 0,
SERVO_enuNotOK ,
SERVO_enuNullPtr

}SERVO_tenuErrorStatus;


SERVO_tenuErrorStatus SERVO_enuWriteAngle(u8 Cpy_u8AngleValue);

#endif /* SERVO_H_ */