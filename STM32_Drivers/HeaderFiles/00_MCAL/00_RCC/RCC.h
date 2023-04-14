/*
 * RCC.h
 *
 *  Created on: Feb 4, 2023
 *      Author: HP
 */

#ifndef RCC_H_
#define RCC_H_

#include "RCC_prv.h"

typedef enum{

RCC_enuOK = 0,
RCC_enuNotOK ,
RCC_enuNullPtr
}RCC_tenuErrorStatus;


typedef enum{
RCC_HSI = 0,
RCC_HSE,
RCC_PLL
}RCC_SystemClk;


typedef enum{
AHB1=0,
AHB2,
APB1,
APB2
}RCC_Buses;


typedef enum{
RCC_84MHZ=1,
RCC_42MHZ,  //note that minimum clk is 48 MHZ for USB to operate
RCC_28MHZ,
RCC_21MHZ,
RCC_ClkNumbers
}RCC_tenuClkValues;
/*******************************************/
/* Function : RCC_ConfigSysClk
 * Input :
 * Output : Error Status
 * Used to configure the Clock of the system
 */
/*******************************************/
RCC_tenuErrorStatus RCC_ConfigSysClk(RCC_tenuClkValues Cpy_u8ClkValue);

/*******************************************/
/* Function : RCC_SwitchSysClk
 * Input : Clock source that you want to switch to
 * Output : Error Status
 * Used to configure the Clock of the system
 */
/*******************************************/
RCC_tenuErrorStatus RCC_SwitchSysClk(RCC_SystemClk Cpy_u8SysClk);

/*System Peripherals to enable clock for*/
/*
///////////AHB1///////////
*GPIOA
*GPIOB
*GPIOC
*GPIOD
*GPIOE
*GPIOH
*CRC
*DMA1
*DMA2
*DMA2
///////////AHB2///////////
*OTGFS

//////////APB1///////////
*TIM2
*TIM3
*TIM4
*TIM5
*WWDG
*SPI2
*SPI3
*USART2
*I2C1
*I2C2
*I2C3
*PWR

///////////APB2///////////
*TIM1
*USART1
*USART6
*ADC1
*SDIO
*SPI1
*SPI4
*SYSCFG
*TIM9
*TIM10
*TIM11
*/

/*******************************************/
/* Function : RCC_Peripheral_EnableSysClk
 * Input : RCC_Peripheral to enable its clock
 * Output : Error Status
 * Used to Enable the peripherals clock
 */
/*******************************************/
RCC_tenuErrorStatus RCC_Peripheral_EnableSysClk(RCC_Buses Cpy_u8Bus, RCC_Peripherals Cpy_u8Peripheral);

/*******************************************/
/* Function : RCC_Peripheral_DisableSysClk
 * Input : RCC_Peripheral to disable its clock
 * Output : Error Status
 * Used to Disable the peripherals clock
 */
/*******************************************/
RCC_tenuErrorStatus RCC_Peripheral_DisableSysClk(RCC_Buses Cpy_u8Bus, RCC_Peripherals Cpy_u8Peripheral);

#endif /* RCC_H_ */
