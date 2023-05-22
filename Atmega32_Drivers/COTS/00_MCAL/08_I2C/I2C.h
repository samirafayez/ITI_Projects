/*
 * I2C.h
 *
 * Created: 4/16/2023 8:27:23 PM
 *  Author: HP
 */ 


#ifndef I2C_H_
#define I2C_H_



typedef enum
{
	I2C_enuOk=0,
	I2C_enuNotOk,
	I2C_enuNullPtr
	
}I2C_tenuErrorStatus;



I2C_tenuErrorStatus I2C_enuInit(void);
I2C_tenuErrorStatus I2C_enuSendStartCondition(void);
I2C_tenuErrorStatus I2C_enuSendRepeatedStart(void);
I2C_tenuErrorStatus I2C_enuSlaveAddressPlusWrite(u8 Cpy_u8SlaveAddress);
I2C_tenuErrorStatus I2C_enuSlaveAddressPlusRead(u8 Cpy_u8SlaveAddress);
I2C_tenuErrorStatus I2C_enuWriteData(u8 Cpy_u8Data);
I2C_tenuErrorStatus I2C_enuReceiveData(u8 * Add_pu8Data);
I2C_tenuErrorStatus I2C_enuSendStopCondition(void);



#endif /* I2C_H_ */