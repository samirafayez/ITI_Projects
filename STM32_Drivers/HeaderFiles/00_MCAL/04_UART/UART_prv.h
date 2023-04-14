/*
 * UART_prv.h
 *
 *  Created on: Apr 7, 2023
 *      Author: HP
 */

#ifndef UART_PRV_H_
#define UART_PRV_H_

#define APB1PERIPH_BASE	0x40000000UL
#define APB2PERIPH_BASE	0x40007400UL


typedef struct{
u32 USART_SR;
u32 USART_DR;
u32 USART_BRR;
u32 USART_CR1;
u32 USART_CR2;
u32 USART_CR3;
u32 USART_GTPR;
}UART_tstrUARTRegisters;


#define UART1_BASEADDR	(UART_tstrUARTRegisters *)(APB2PERIPH_BASE + 0x00003600UL)
#define UART2_BASEADDR	(UART_tstrUARTRegisters *)(APB1PERIPH_BASE + 0x00004000UL)
#define UART6_BASEADDR	(UART_tstrUARTRegisters *)(APB2PERIPH_BASE + 0x00004400UL)

volatile UART_tstrUARTRegisters * const UART[UART_enuUARTsNumber] = { UART1_BASEADDR, UART2_BASEADDR, UART6_BASEADDR};


//SR
#define TXE    7
#define TC     6
#define RXNE   5



//CR1
#define OVER8  15
#define UE     13
#define M      12
#define PCE    10
#define PS     9
#define PEIE   8
#define TXEIE  7
#define TCIE   6
#define RXNEIE 5
#define TE     3
#define RE     2


//CR2
#define LINEN   14
#define STOP1   13
#define STOP0   12
#define CLKEN   11
#define CPOL    10
#define CPHA    9
#define LBDIE   6


//CR3
#define CTSIE   10
#define CTSE    9
#define RTSE    8
#define DMAT    7
#define DMAR    6
#define SCEN    5


#endif /* UART_PRV_H_ */
