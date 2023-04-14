/*
 * DMA.c
 *
 *  Created on: Apr 13, 2023
 *      Author: HP
 */


#include "std_defines.h"
#include "bit_math.h"
#include "05_DMA/DMA.h"
#include "05_DMA/DMA_Cfg.h"
#include "05_DMA/DMA_prv.h"


static void(*DMA_CallBackFunctionHalfTransfer[DMA_enuDMANumber][DMA_enuStreamNumber])(void);
static void(*DMA_CallBackFunctionTransferComplete[DMA_enuDMANumber][DMA_enuStreamNumber])(void);



DMA_tenuErrorStatus DMA_enuInit(DMA_tenuId DMA_enuId, DMA_tstrStreamCFG * DMA_strStreamCFG)
{
	DMA_tenuErrorStatus Loc_u8State = DMA_enuOK;
	u32 Loc_u32TempReg = 0;
	//DMA1_REG->DMA_tstrStreamRegs.SxCR[DMA_strStreamCFG->DMA_enuStream]
	if(DMA_strStreamCFG->DMA_enuStream < DMA_enuStreamNumber)
	{

		Loc_u32TempReg = (DMA_strStreamCFG->DMA_enuChannel << 25) | (DMA_strStreamCFG->DMA_enuMemoryBurst << 23) |
				(DMA_strStreamCFG->DMA_enuPeripheralBurst << 21) | (DMA_strStreamCFG->DMA_DoubleBufferMode << 18) |
				(DMA_strStreamCFG->DMA_enuPriorityLevel << 16) | (DMA_strStreamCFG->DMA_enuMemoryDataSize << 13) |
				(DMA_strStreamCFG->DMA_enuPeripheralDataSize << 11) | (DMA_strStreamCFG->DMA_enuMemoryAIncrement << 10) |
				(DMA_strStreamCFG->DMA_enuPeripheralAIncrement << 9) | (DMA_strStreamCFG->DMA_enuCircularMode << 8) |
				(DMA_strStreamCFG->DMA_enuDataDirection << 6) | (DMA_strStreamCFG->DMA_tstrInterrupt.DMA_enuTransferComplete << 4) |
				(DMA_strStreamCFG->DMA_tstrInterrupt.DMA_enuHalfTransfer << 3) | (DMA_strStreamCFG->DMA_tstrInterrupt.DMA_enuTransferError <<2) |
				(DMA_strStreamCFG->DMA_tstrInterrupt.DMA_enuDirectMode << 1) | (1<<0);

		if(DMA_enuId == DMA_enuDMA1)
		{
			DMA1_REG->DMA_tstrStreamRegs[DMA_strStreamCFG->DMA_enuStream].SxCR = Loc_u32TempReg;
		}
		else if(DMA_enuId == DMA_enuDMA2)
		{
			DMA2_REG->DMA_tstrStreamRegs[DMA_strStreamCFG->DMA_enuStream].SxCR = Loc_u32TempReg;
		}
		else
		{
			Loc_u8State = DMA_enuNotOK;
		}
		//DMA1->DMA_tstrStreamRegs.SxCR[DMA_strStreamCFG->DMA_enuStream] = 0;

	}
	else
	{
		Loc_u8State = DMA_enuNotOK;
	}


	return Loc_u8State;

}




DMA_tenuErrorStatus DMA_enuDataConfiguration (DMA_tenuId DMA_enuId, DMA_tstrDataTransferInfo * DMA_strDataTransferInfo)
{
	DMA_tenuErrorStatus Loc_u8State = DMA_enuOK;

	if(DMA_enuId == DMA_enuDMA1)
	{
		DMA1_REG->DMA_tstrStreamRegs[DMA_strDataTransferInfo->DMA_enuStream].SxNDTR = DMA_strDataTransferInfo->DMA_u16DataItems;
		DMA1_REG->DMA_tstrStreamRegs[DMA_strDataTransferInfo->DMA_enuStream].SxM0AR = DMA_strDataTransferInfo->DMA_u32MemoryAddress_0;
		DMA1_REG->DMA_tstrStreamRegs[DMA_strDataTransferInfo->DMA_enuStream].SxM1AR = DMA_strDataTransferInfo->DMA_u32MemoryAddress_1;
		DMA1_REG->DMA_tstrStreamRegs[DMA_strDataTransferInfo->DMA_enuStream].SxPAR = DMA_strDataTransferInfo->DMA_u32PeripheralAddress;
	}
	else if(DMA_enuId == DMA_enuDMA2)
	{
		DMA2_REG->DMA_tstrStreamRegs[DMA_strDataTransferInfo->DMA_enuStream].SxNDTR = DMA_strDataTransferInfo->DMA_u16DataItems;
		DMA2_REG->DMA_tstrStreamRegs[DMA_strDataTransferInfo->DMA_enuStream].SxM0AR = DMA_strDataTransferInfo->DMA_u32MemoryAddress_0;
		DMA2_REG->DMA_tstrStreamRegs[DMA_strDataTransferInfo->DMA_enuStream].SxM1AR = DMA_strDataTransferInfo->DMA_u32MemoryAddress_1;
		DMA2_REG->DMA_tstrStreamRegs[DMA_strDataTransferInfo->DMA_enuStream].SxPAR = DMA_strDataTransferInfo->DMA_u32PeripheralAddress;
	}
	else
	{
		Loc_u8State = DMA_enuNotOK;
	}

	return Loc_u8State;
}



DMA_tenuErrorStatus DMA_enuSetCallBackFunc(DMA_tenuId DMA_enuId, DMA_tenuStream DMA_enuStream, DMA_tenuInterruptSrc DMA_enuInterruptSrc, void(*CallBackFunction)(void))
{
	DMA_tenuErrorStatus Loc_u8State = DMA_enuOK;
	if(CallBackFunction != NULL)
	{
		if((DMA_enuId < DMA_enuDMANumber) && (DMA_enuStream < DMA_enuStreamNumber ))
		{
			if(DMA_enuInterruptSrc == DMA_enuHalfTransfer)
			{
				DMA_CallBackFunctionHalfTransfer[DMA_enuId][DMA_enuStream] = CallBackFunction;
			}
			else if(DMA_enuInterruptSrc == DMA_enuTransferComplete)
			{
				DMA_CallBackFunctionTransferComplete[DMA_enuId][DMA_enuStream] = CallBackFunction;
			}
			else
			{
				Loc_u8State = DMA_enuNotOK;
			}

		}
		else
		{
			Loc_u8State = DMA_enuNotOK;
		}

	}
	else
	{
		Loc_u8State = DMA_enuNullPtr;
	}

	return Loc_u8State;
}



void DMA1_Stream0_IRQHandler(void)
{

	if((GET_BIT(DMA1_REG->DMA_LISR, HTIF0) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream1] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_LIFCR, HTIF0);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream1]();

	}
	else
	{
		//Do Nothing
	}

	if((GET_BIT(DMA1_REG->DMA_LISR, TCIF0) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream1] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_LIFCR, TCIF0);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream1]();

	}
	else
	{
		//Do Nothing
	}

}

void DMA1_Stream1_IRQHandler(void)
{
	if((GET_BIT(DMA1_REG->DMA_LISR, HTIF1) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream2] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_LIFCR, HTIF1);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream2]();

	}
	else
	{
		//Do Nothing
	}

	if((GET_BIT(DMA1_REG->DMA_LISR, TCIF1) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream2] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_LIFCR, TCIF1);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream2]();

	}
	else
	{
		//Do Nothing
	}
}

void DMA1_Stream2_IRQHandler(void)
{
	if((GET_BIT(DMA1_REG->DMA_LISR, HTIF2) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream3] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_LIFCR, HTIF2);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream3]();

	}
	else
	{
		//Do Nothing
	}


	if((GET_BIT(DMA1_REG->DMA_LISR, TCIF2) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream3] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_LIFCR, TCIF2);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream3]();

	}
	else
	{
		//Do Nothing
	}

}

void DMA1_Stream3_IRQHandler(void)
{
	if((GET_BIT(DMA1_REG->DMA_LISR, HTIF3) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream4] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_LIFCR, HTIF3);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream4]();

	}
	else
	{
		//Do Nothing
	}

	if((GET_BIT(DMA1_REG->DMA_LISR, TCIF3) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream4] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_LIFCR, TCIF3);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream4]();

	}
	else
	{
		//Do Nothing
	}

}

void DMA1_Stream4_IRQHandler(void)
{

	if((GET_BIT(DMA1_REG->DMA_HISR, HTIF0) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream5] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_HIFCR, HTIF0);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream5]();

	}
	else
	{
		//Do Nothing
	}

	if((GET_BIT(DMA1_REG->DMA_HISR, TCIF0) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream5] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_HIFCR, TCIF0);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream5]();

	}
	else
	{
		//Do Nothing
	}

}


void DMA1_Stream5_IRQHandler(void)
{

	if((GET_BIT(DMA1_REG->DMA_HISR, HTIF1) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream6] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_HIFCR, HTIF1);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream6]();

	}
	else
	{
		//Do Nothing
	}

	if((GET_BIT(DMA1_REG->DMA_HISR, TCIF1) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream6] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_HIFCR, TCIF1);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream6]();

	}
	else
	{
		//Do Nothing
	}

}



void DMA1_Stream6_IRQHandler(void)
{

	if((GET_BIT(DMA1_REG->DMA_HISR, HTIF2) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream7] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_HIFCR, HTIF2);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream7]();

	}
	else
	{
		//Do Nothing
	}

	if((GET_BIT(DMA1_REG->DMA_HISR, TCIF2) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream7] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_HIFCR, TCIF2);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream7]();

	}
	else
	{
		//Do Nothing
	}
}

void DMA1_Stream7_IRQHandler(void)
{

	if((GET_BIT(DMA1_REG->DMA_HISR, HTIF3) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream8] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_HIFCR, HTIF3);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA1][DMA_enuStream8]();

	}
	else
	{
		//Do Nothing
	}

	if((GET_BIT(DMA1_REG->DMA_HISR, TCIF3) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream8] != NULL) )
	{

		SET_BIT(DMA1_REG->DMA_HIFCR, TCIF3);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA1][DMA_enuStream8]();

	}
	else
	{
		//Do Nothing
	}
}



void DMA2_Stream0_IRQHandler(void)
{

	if((GET_BIT(DMA2_REG->DMA_LISR, HTIF0) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA2][DMA_enuStream1] != NULL) )
	{

		SET_BIT(DMA2_REG->DMA_LIFCR, HTIF0);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA2][DMA_enuStream1]();

	}
	else
	{
		//Do Nothing
	}

	if((GET_BIT(DMA2_REG->DMA_LISR, TCIF0) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA2][DMA_enuStream1] != NULL) )
	{

		SET_BIT(DMA2_REG->DMA_LIFCR, TCIF0);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA2][DMA_enuStream1]();

	}
	else
	{
		//Do Nothing
	}

}

void DMA2_Stream1_IRQHandler(void)
{
	if((GET_BIT(DMA2_REG->DMA_LISR, HTIF1) == 1) && (DMA_CallBackFunctionHalfTransfer[DMA_enuDMA2][DMA_enuStream2] != NULL) )
	{

		SET_BIT(DMA2_REG->DMA_LIFCR, HTIF1);
		DMA_CallBackFunctionHalfTransfer[DMA_enuDMA2][DMA_enuStream2]();

	}
	else
	{
		//Do Nothing
	}

	if((GET_BIT(DMA2_REG->DMA_LISR, TCIF1) == 1) && (DMA_CallBackFunctionTransferComplete[DMA_enuDMA2][DMA_enuStream2] != NULL) )
	{

		SET_BIT(DMA2_REG->DMA_LIFCR, TCIF1);
		DMA_CallBackFunctionTransferComplete[DMA_enuDMA2][DMA_enuStream2]();

	}
	else
	{
		//Do Nothing
	}
}

