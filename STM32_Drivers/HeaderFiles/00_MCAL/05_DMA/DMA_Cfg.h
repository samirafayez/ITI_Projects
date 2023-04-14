/*
 * DMA_Cfg.h
 *
 *  Created on: Apr 13, 2023
 *      Author: HP
 */

#ifndef DMA_CFG_H_
#define DMA_CFG_H_


typedef enum
{
	DMA_enuDMA1 = 0,
	DMA_enuDMA2,
	DMA_enuDMANumber

}DMA_tenuId;



typedef enum
{
	DMA_enuStream1=0,
	DMA_enuStream2,
	DMA_enuStream3,
	DMA_enuStream4,
	DMA_enuStream5,
	DMA_enuStream6,
	DMA_enuStream7,
	DMA_enuStream8,
	DMA_enuStreamNumber
}DMA_tenuStream;


typedef enum
{
	DMA_enuChannel1=0,
	DMA_enuChannel2,
	DMA_enuChannel3,
	DMA_enuChannel4,
	DMA_enuChannel5,
	DMA_enuChannel6,
	DMA_enuChannel7,
	DMA_enuChannel8
}DMA_tenuChannel;



typedef enum
{
	VeryHighPriority=0,
	HighPriority,
	MediumPriority,
	LowPriority
}DMA_tenuPriorityLevel;


typedef enum
{
	DMA_enuByte=0,
	DMA_enuHalfWord,
	DMA_enuWord,
}DMA_tenuDataSize;




typedef enum
{
	DMA_enuPeripheral2Memory=0,
	DMA_enuMemory2Peripheral,
	DMA_enuMemory2Memory
}DMA_tenuDataDirection;



typedef enum
{
	DMA_enuSingle = 0,
	DMA_enuInc_4_Beats,
	DMA_enuInc_8_Beats,
	DMA_enuInc_16_Beats

}DMA_tenuBurst;


typedef enum
{
	DMA_enuHalfTransfer=0,
	DMA_enuTransferComplete
}DMA_tenuInterruptSrc;


typedef enum
{
	DMA_Disabled=0,
	DMA_Enabled
}DMA_tenuEN;



typedef struct{

	DMA_tenuStream DMA_enuStream;
	DMA_tenuChannel DMA_enuChannel;
	DMA_tenuPriorityLevel DMA_enuPriorityLevel;
	DMA_tenuEN DMA_DoubleBufferMode;
	DMA_tenuEN DMA_enuCircularMode;
	DMA_tenuDataSize DMA_enuMemoryDataSize;
	DMA_tenuDataSize DMA_enuPeripheralDataSize;
	DMA_tenuBurst DMA_enuMemoryBurst;
	DMA_tenuBurst DMA_enuPeripheralBurst;
	DMA_tenuEN DMA_enuMemoryAIncrement;
	DMA_tenuEN DMA_enuPeripheralAIncrement;
	DMA_tenuDataDirection DMA_enuDataDirection;
	struct {

		DMA_tenuEN DMA_enuTransferComplete;
		DMA_tenuEN DMA_enuHalfTransfer;
		DMA_tenuEN DMA_enuTransferError;
		DMA_tenuEN DMA_enuDirectMode;
	}DMA_tstrInterrupt;


}DMA_tstrStreamCFG;





typedef struct{
	DMA_tenuStream DMA_enuStream;
	u32 DMA_u32PeripheralAddress;
	u32 DMA_u32MemoryAddress_0;
	u32 DMA_u32MemoryAddress_1;
	u16 DMA_u16DataItems;

}DMA_tstrDataTransferInfo;




#endif /* DMA_CFG_H_ */
