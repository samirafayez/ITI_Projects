/*
 * SPI_prv.h
 *
 * Created: 4/4/2023 3:06:09 PM
 *  Author: HP
 */ 
#ifndef SPI_PRV_H_
#define SPI_PRV_H_

#define SPCR *((volatile u8 *)0x2D)
#define SPIE 7
#define SPE  6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0
#define SPSR *((volatile u8 *)0x2E)
#define SPIF  7
#define WCOL  6
#define SPI2X 0
#define SPDR *((volatile u8 *)0x2F)







#endif /* SPI_PRV_H_ */