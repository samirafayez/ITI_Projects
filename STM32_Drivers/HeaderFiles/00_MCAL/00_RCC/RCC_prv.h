/*
 * RCC_prv.h
 *
 *  Created on: Feb 4, 2023
 *      Author: HP
 */

#ifndef RCC_PRV_H_
#define RCC_PRV_H_






#define RCC_CR  *((volatile u32 *)0x40023800)
#define HSI_ON 0
#define HSI_RDY 1
#define HSE_ON 16
#define HSE_RDY 17
#define CSS_ON 19
#define PLL_ON 24
#define PLL_RDY 25


#define RCC_PLLCFGR *((volatile u32 *)0x40023804)
#define PLL_SRC 22
#define PLLN 6
#define PLLP 16


#define RCC_CFGR *((volatile u32 *)0x40023808)
#define SW0 0
#define SW1 1
#define SWS0 2
#define SWS1 3


#define RCC_AHB1ENR *((volatile u32 *)0x40023830)
#define RCC_AHB2ENR *((volatile u32 *)0x40023834)
#define RCC_APB1ENR *((volatile u32 *)0x40023840)
#define RCC_APB2ENR *((volatile u32 *)0x40023844)



typedef enum {
GPIOA=0,
GPIOB,
GPIOC,
GPIOD,
GPIOE,
GPIOH=7,
CRC=12,
DMA1=21,
DMA2,
/*AHB1*/
OTGFS=7,
/*AHB2*/
TIM2=0,
TIM3,
TIM4,
TIM5,
WWDG=11,
SPI2=14,
SPI3,
USART2=17,
I2C1=21,
I2C2,
I2C3,
PWR=28,
/*APB1*/
TIM1=0,
USART1=4,
USART6,
ADC1=8,
SDIO=11,
SPI1,
SPI4,
SYSCFG,
TIM9=16,
TIM10,
TIM11
/*APB2*/
}RCC_Peripherals;

/*APB1*/

#endif /* RCC_PRV_H_ */
