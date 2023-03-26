/*
 * UART_prv.h
 *
 * Created: 3/18/2023 8:51:41 AM
 *  Author: HP
 */ 


#ifndef UART_PRV_H_
#define UART_PRV_H_


#define UART_ParityMode_CLRMask      0b11001111
#define UART_UBRRH_HighNibbleCLRMask 0b00001111


#define UDR   *((volatile u8 *)0x2C)
#define UCSRA *((volatile u8 *)0x2B)
#define RXC  7
#define TXC  6
#define UDRE 5
#define MPCM 0
#define UCSRB *((volatile u8 *)0x2A)
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN  4
#define TXEN  3
#define UCSZ2 2
#define UCSRC *((volatile u8 *)0x40)
#define URSEL 7
#define UMSEL 6
#define UPM1  5
#define UPM0  4
#define USBS  3
#define UCSZ1 2
#define UCSZ0 1
#define UCPOL 0
#define UBRRH *((volatile u8 *)0x40)
#define UBRRL *((volatile u8 *)0x29)




#endif /* UART_PRV_H_ */