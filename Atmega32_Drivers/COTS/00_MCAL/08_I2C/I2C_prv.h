/*
 * I2C_prv.h
 *
 * Created: 4/16/2023 8:28:11 PM
 *  Author: HP
 */ 


#ifndef I2C_PRV_H_
#define I2C_PRV_H_


#define TWBR *((volatile u8 *)0x20)
#define TWCR *((volatile u8 *)0x56)
#define TWSR *((volatile u8 *)0x21)
#define TWDR *((volatile u8 *)0x23)
#define TWAR *((volatile u8 *)0x22)

#define TWINT 7
#define TWEA  6
#define TWSTA 5
#define TWSTO 4
#define TWEN  2


#endif /* I2C_PRV_H_ */