/*
 * IncFile1.h
 *
 * Created: 1/17/2023 9:31:44 PM
 *  Author: HP
 */ 




#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(REG,BIT)	REG |= (1<<BIT)
#define CLR_BIT(REG,BIT)	REG &= ~(1<<BIT)
#define TGL_BIT(REG,BIT)	REG ^= (1<<BIT)
#define GET_BIT(REG,BIT)	((REG>>BIT)&1)
#define SET_HIG_NIB(REG)	REG |= 0xF0
#define CLR_HIG_NIB(REG)	REG &= 0x0F
#define GET_HIG_NIB(REG)	REG = (REG>>4) & (0x0F)
#define TGL_HIG_NIB(REG)	REG ^= 0xF0
#define SET_LOW_NIB(REG)	REG |= 0x0F
#define CLR_LOW_NIB(REG)	REG &= 0xF0
#define GET_LOW_NIB(REG)	REG &= 0x0F
#define TGL_LOW_NIB(REG)	REG ^= 0x0F
#define ASSIGN_REG(REG,VALUE)	REG = VALUE
#define ASSIGN_HIG_NIB(REG,VALUE)	REG |= VALUE << 4
#define ASSIGN_LOW_NIB(REG,VALUE)	REG |= (VALUE & 0x0F)
#define SHIFT_RIGHT(REG,VALUE)		REG>>=VALUE
#define SHIFT_SHIFT(REG,VALUE)		REG<<=VALUE
#define CLR_RIGHT_SHIFT(REG,VALUE)	REG = (REG>>VALUE)|(REG<<sizeof(REG)-VALUE)
#define CLR_LEFT_SHIFT(REG,VALUE)	REG = (REG<<VALUE)|(REG>>sizeof(REG)-VALUE)


#endif /* BIT_MATH_H_ */




