/*
 * DMA_prv.h
 *
 *  Created on: Apr 13, 2023
 *      Author: HP
 */

#ifndef DMA_PRV_H_
#define DMA_PRV_H_


typedef struct{

	u32 DMA_LISR;
	u32 DMA_HISR;
	u32 DMA_LIFCR;
	u32 DMA_HIFCR;
	struct
	{
		u32 SxCR;
		u32 SxNDTR;
		u32 SxPAR;
		u32 SxM0AR;
		u32 SxM1AR;
		u32 SxFCR;

	}DMA_tstrStreamRegs[8];

}DMA_tstrRegisters;




//#define DMA1_BaseAddress  (DMA_tstrRegisters*)(0x40026000UL)

//#define DMA2_BaseAddress  (DMA_tstrRegisters*)(0x40026400UL)


volatile DMA_tstrRegisters * const DMA1_REG = (DMA_tstrRegisters *) (0x40026000UL);
volatile DMA_tstrRegisters * const DMA2_REG = (DMA_tstrRegisters *) (0x40026400UL);



//DMA_LISR
#define TCIF0    5
#define TCIF1    11
#define TCIF2    21
#define TCIF3    27
#define HTIF0    4
#define HTIF1    10
#define HTIF2    20
#define HTIF3    26
//DMA_HISR
#define TCIF4    5
#define TCIF5    11
#define TCIF6    21
#define TCIF7    27
#define HTIF4    4
#define HTIF5    10
#define HTIF6    20
#define HTIF7    26





#endif /* DMA_PRV_H_ */
