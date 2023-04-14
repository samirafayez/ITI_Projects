/*
 * GPIO_prv.h
 *
 *  Created on: Feb 16, 2023
 *      Author: HP
 */

#ifndef GPIO_PRV_H_
#define GPIO_PRV_H_

#include "std_defines.h"

#define AHB1PERIPH_BASE	0x40020000UL


typedef struct{

u32 GPIOx_MODER;
u32 GPIOx_OTYPER;
u32 GPIOx_OSPEEDR;
u32 GPIOx_PUPDR ;
u32 GPIOx_IDR ;
u32 GPIOx_ODR;
u32 GPIOx_BSRR;
u32 GPIOx_LCKR;
u32 GPIOx_AFRL;
u32 GPIOx_AFRH;

}GPIO_tstrRegisters;


#define GPIOA_BASEADDR	(GPIO_tstrRegisters *)(AHB1PERIPH_BASE + 0x00000000UL)
#define GPIOB_BASEADDR	(GPIO_tstrRegisters *)(AHB1PERIPH_BASE + 0x00000400UL)
#define GPIOC_BASEADDR	(GPIO_tstrRegisters *)(AHB1PERIPH_BASE + 0x00000800UL)

//#define GPIOA_REG	((GPIO_tstrRegisters *)GPIOA_BASEADDR)
//#define GPIOB_REG	((GPIO_tstrRegisters *)GPIOE_BASEADDR)
//#define GPIOC_REG	((GPIO_tstrRegisters *)GPIOH_BASEADDR)


volatile GPIO_tstrRegisters * const GPIOA_REG =  GPIOA_BASEADDR;
volatile GPIO_tstrRegisters * const GPIOB_REG =  GPIOB_BASEADDR;
volatile GPIO_tstrRegisters * const GPIOC_REG =  GPIOC_BASEADDR;




#endif /* GPIO_PRV_H_ */
