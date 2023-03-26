/*
 * INT_piv.h
 *
 * Created: 1/26/2023 7:41:21 PM
 *  Author: HP
 */ 


#ifndef INT_PRV_H_
#define INT_PRV_H_





#define GICR  *((volatile u8 *)0x5B)
#define MCUCSR  *((volatile u8 *)0x54)
#define MCUCR  *((volatile u8 *)0x55)
#define GIFR  *((volatile u8 *)0x5A)



#endif /* INT_PRV_H_ */