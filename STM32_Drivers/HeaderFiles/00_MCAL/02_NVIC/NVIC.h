/*
 * NVIC.h
 *
 *  Created on: Mar 2, 2023
 *      Author: HP
 */

#ifndef NVIC_H_
#define NVIC_H_


typedef enum{
	NVIC_enuOk=0,
	NVIC_enuNotOk,
	NVIC_enuNullPtr
}NVIC_tenuErrorStatus;


typedef enum{
	NVIC_NMI            = -14,  /**< Non-maskable interrupt */
	NVIC_HARDFAULT      = -13,  /**< Hard fault (all class of fault) */
	NVIC_MEM_MANAGE     = -12,  /**< Memory management */
	NVIC_BUS_FAULT      = -11,  /**< Bus fault: prefetch fault, memory
	                                     access fault. */
	NVIC_USAGE_FAULT    = -10,  /**< Usage fault: Undefined instruction or
	                                     illegal state. */
	NVIC_SVC            = -5,   /**< System service call via SWI insruction */
	NVIC_DEBUG_MON      = -4,   /**< Debug monitor */
	NVIC_PEND_SVC       = -2,   /**< Pendable request for system service */
	NVIC_SYSTICK        = -1,   /**< System tick timer */
	NVIC_WWDG           = 0,    /**< Window watchdog interrupt */
	NVIC_PVD            = 1,    /**< PVD through EXTI line detection */
	NVIC_TAMPER         = 2,    /**< Tamper */
	NVIC_RTC            = 3,    /**< Real-time clock */
	NVIC_FLASH          = 4,    /**< Flash */
	NVIC_RCC            = 5,    /**< Reset and clock control */
	NVIC_EXTI0          = 6,    /**< EXTI line 0 */
	NVIC_EXTI1          = 7,    /**< EXTI line 1 */
	NVIC_EXTI2          = 8,    /**< EXTI line 2 */
	NVIC_EXTI3          = 9,    /**< EXTI line 3 */
	NVIC_EXTI4          = 10,   /**< EXTI line 4 */
	NVIC_DMA_CH1        = 11,   /**< DMA1 channel 1 */
	NVIC_DMA_CH2        = 12,   /**< DMA1 channel 2 */
	NVIC_DMA_CH3        = 13,   /**< DMA1 channel 3 */
	NVIC_DMA_CH4        = 14,   /**< DMA1 channel 4 */
	NVIC_DMA_CH5        = 15,   /**< DMA1 channel 5 */
	NVIC_DMA_CH6        = 16,   /**< DMA1 channel 6 */
	NVIC_DMA_CH7        = 17,   /**< DMA1 channel 7 */
	NVIC_ADC_1_2        = 18,   /**< ADC1 and ADC2 */
	NVIC_USB_HP_CAN_TX  = 19,   /**< USB high priority or CAN TX */
	NVIC_USB_LP_CAN_RX0 = 20,   /**< USB low priority or CAN RX0 */
	NVIC_CAN_RX1        = 21,   /**< CAN RX1 */
	NVIC_CAN_SCE        = 22,   /**< CAN SCE */
	NVIC_EXTI_9_5       = 23,   /**< EXTI line [9:5] */
	NVIC_TIMER1_BRK_TIMER9 = 24, /**< Timer 1 break, Timer 9. */
	NVIC_TIMER1_UP_TIMER10 = 25, /**< Timer 1 update, Timer 10. */
	NVIC_TIMER1_TRG_COM_TIMER11 = 26, /**<
	 * Timer 1 trigger and commutation,
	 * Timer 11. */
	NVIC_TIMER1_CC      = 27,   /**< Timer 1 capture/compare */
	NVIC_TIMER2         = 28,   /**< Timer 2 */
	NVIC_TIMER3         = 29,   /**< Timer 3 */
	NVIC_TIMER4         = 30,   /**< Timer 4 */
	NVIC_I2C1_EV        = 31,   /**< I2C1 event */
	NVIC_I2C1_ER        = 32,   /**< I2C1 error */
	NVIC_I2C2_EV        = 33,   /**< I2C2 event */
	NVIC_I2C2_ER        = 34,   /**< I2C2 error */
	NVIC_SPI1           = 35,   /**< SPI1 */
	NVIC_SPI2           = 36,   /**< SPI2 */
	NVIC_USART1         = 37,   /**< USART1 */
	NVIC_USART2         = 38,   /**< USART2 */
	NVIC_USART3         = 39,   /**< USART3 */
	NVIC_EXTI_15_10     = 40,   /**< EXTI line [15:10] */
	NVIC_RTCALARM       = 41,   /**< RTC alarm through EXTI line */
	NVIC_USBWAKEUP      = 42,   /**< USB wakeup from suspend through
	                                     EXTI line */
	NVIC_TIMER8_BRK_TIMER12 = 43, /**< Timer 8 break, timer 12  */
	NVIC_TIMER8_UP_TIMER13 = 44, /**< Timer 8 update, timer 13 */
	NVIC_TIMER8_TRG_COM_TIMER14 = 45, /**<
	 * Timer 8 trigger and commutation,
	 * Timer 14. */
	NVIC_TIMER8_CC      = 46,   /**< Timer 8 capture/compare */
	NVIC_ADC3           = 47,   /**< ADC3 */
	NVIC_FSMC           = 48,   /**< FSMC */
	NVIC_SDIO           = 49,   /**< SDIO */
	NVIC_TIMER5         = 50,   /**< Timer 5 */
	NVIC_SPI3           = 51,   /**< SPI3 */
	NVIC_UART4          = 52,   /**< UART4 */
	NVIC_UART5          = 53,   /**< UART5 */
	NVIC_TIMER6         = 54,   /**< Timer 6 */
	NVIC_TIMER7         = 55,   /**< Timer 7 */
	NVIC_DMA2_CH1       = 56,   /**< DMA2 channel 1 */
	NVIC_DMA2_CH2       = 57,   /**< DMA2 channel 2 */
	NVIC_DMA2_CH3       = 58,   /**< DMA2 channel 3 */
	NVIC_DMA2_CH_4      = 59,   /**< DMA2 channels 4 */
	NVIC_DMA2_CH5       = 60,   /**< DMA2 channel 5 (stream 4) */
	NVIC_ETH            = 61,   /**< ETH Global Interrupt */
	NVIC_ETHWAKEUP      = 62,   /**< ETH Wakeup through EXTI line */
	NVIC_CAN2_TX        = 63,   /**< CAN2 TX  */
	NVIC_CAN2_RX0       = 64,   /**< CAN2 RX0 */
	NVIC_CAN2_RX1       = 65,   /**< CAN2 RX1 */
	NVIC_CAN2_SCE       = 66,   /**< CAN2 SCE */
	NVIC_OTG_FS         = 67,   /**< USB OTG */
	NVIC_DMA2_CH6       = 68,   /**< DMA2 channel 6 (stream 5) */
	NVIC_DMA2_CH7       = 69,   /**< DMA2 channel 7 (stream 6) */
	NVIC_DMA2_CH8       = 70,   /**< DMA2 channel 8 (stream 7) */
	NVIC_USART6         = 71,   /**< USART6 */
	NVIC_I2C3_EV        = 72,   /**< I2C3 event */
	NVIC_I2C3_ER        = 73,   /**< I2C3 error */
	NVIC_OTG_HS_EP1_OUT = 74,   /**< USB OTG HS End Point 1 Out */
	NVIC_OTG_HS_EP1_IN  = 75,   /**< USB OTG HS End Point 1 In */
	NVIC_OTG_HS_WKUP    = 76,   /**< USB OTG HS Wakeup Throught EXTI */
	NVIC_OTG_HS         = 77,   /**< USB OTG HS */
	NVIC_DCMI           = 78,   /**< DCMI */
	NVIC_CRYP           = 79,   /**< CRYP crypto */
	NVIC_HASH_RNG       = 80,   /**< Hash and RNG */
	NVIC_FPU            = 81,   /**< FPU */
	NVIC_UART7          = 82,   /**< UART7 */
	NVIC_UART8          = 83,   /**< UART8 */
	NVIC_SPI4           = 84,   /**< SPI4 */
	NVIC_SPI5           = 85,   /**< SPI5 */
	NVIC_SPI6           = 86,   /**< SPI 6 */
	NVIC_SAI1           = 87,   /**< SAI1 */
	NVIC_LCDTFT         = 88,   /**< LTDC */
	NVIC_LCDTFT_ER      = 89,   /**< LTDC global Error */
	NVIC_DMA2D          = 90,   /**< DMA2D */
	NVIC_QUADSPI        = 91,   /**< QuadSPI */
	NVIC_DSI            = 92,   /**< DSI */
	NVIC_IRQnumber
}IRQtenu_number;



//NVIC_tenuErrorStatus NVIC_GlobalInterruptEN(void);
NVIC_tenuErrorStatus NVIC_enuDisable(IRQtenu_number Cpy_IRQn);
NVIC_tenuErrorStatus NVIC_enuEnable(IRQtenu_number Cpy_IRQn);
NVIC_tenuErrorStatus NVIC_enuGetActiveStatus(IRQtenu_number Cpy_IRQn, u32 * Cpy_u32Status);
NVIC_tenuErrorStatus NVIC_enuSetPending(IRQtenu_number Cpy_IRQn);
NVIC_tenuErrorStatus NVIC_enuClearPending(IRQtenu_number Cpy_IRQn);
NVIC_tenuErrorStatus NVIC_enuSetPriority(IRQtenu_number Cpy_IRQn,u32 Cpy_u32Priority);
NVIC_tenuErrorStatus NVIC_SetPriorityGrouping(u32 Cpy_u32GroupingPriority);
NVIC_tenuErrorStatus NVIC_SetCallBackFunction(IRQtenu_number Cpy_IRQn, void(*Cpy_CallBackPtr)(void));




#endif /* NVIC_H_ */
