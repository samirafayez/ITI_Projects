/*
 * DMA.h
 *
 *  Created on: Apr 13, 2023
 *      Author: HP
 */

#ifndef DMA_H_
#define DMA_H_

#include "DMA_Cfg.h"




typedef enum{
	DMA_enuOK=0,
	DMA_enuNotOK,
	DMA_enuNullPtr
}DMA_tenuErrorStatus;



DMA_tenuErrorStatus DMA_enuInit(DMA_tenuId DMA_enuId, DMA_tstrStreamCFG * DMA_strStreamCFG);
DMA_tenuErrorStatus DMA_enuDataConfiguration(DMA_tenuId DMA_enuId, DMA_tstrDataTransferInfo * DMA_strDataTransferInfo);
DMA_tenuErrorStatus DMA_enuSetCallBackFunc(DMA_tenuId DMA_enuId, DMA_tenuStream DMA_enuStream, DMA_tenuInterruptSrc DMA_enuInterruptSrc, void(*CallBackFunction)(void));



#endif /* DMA_H_ */
