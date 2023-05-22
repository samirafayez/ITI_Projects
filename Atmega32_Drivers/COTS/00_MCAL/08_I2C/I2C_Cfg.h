/*
 * I2C_Cfg.h
 *
 * Created: 4/16/2023 8:27:57 PM
 *  Author: HP
 */ 
#ifndef I2C_CFG_H_
#define I2C_CFG_H_


typedef enum
{
	I2C_enuDisabled=0,
	I2C_enuEnabled
	
}I2C_tenuEN;


typedef enum
{
	I2C_enu1=0,
	I2C_enu4,
	I2C_enu16,
	I2C_enu64
	
}I2C_tenuPrescaler;


typedef struct  
{
	u8 I2C_BitRate;
	I2C_tenuEN I2C_InterruptEN;
	I2C_tenuEN I2C_AcknowledgeEN;
	I2C_tenuPrescaler I2C_Prescaler;
	I2C_tenuEN GeneralCallRecognitionEN;
	u8 I2C_SlaveAddress : 7;
	
	
}I2C_tstrCFG_t;


#endif /* I2C_CFG_H_ */