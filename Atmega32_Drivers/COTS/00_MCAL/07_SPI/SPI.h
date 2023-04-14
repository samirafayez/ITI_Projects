/*
 * SPI.h
 *
 * Created: 4/4/2023 3:05:39 PM
 *  Author: HP
 */ 
#ifndef SPI_H_
#define SPI_H_
#define TIMEOUT 10000000

typedef enum
{
	SPI_enuOk=0,
	SPI_enuNotOk,
	SPI_NullPtr
}SPI_tenuErrorStatus;


typedef enum
{
	SPI_enuMSBFirst=0,
	SPI_enuLSBFirst
}SPI_tenuSPIDataOrder;


typedef enum
{
	SPI_enuSlave=0,
	SPI_enuMaster=1
}SPI_tenuMasterSlaveSel;


typedef enum
{
	SPI_enuIdleZero=0,
	SPI_enuIdleOne
}SPI_tenuClkPolarity;


typedef enum
{
	SPI_enuSampleFirst=0,
	SPI_enuSetupFirst
}SPI_tenuClkPhase;


typedef enum
{
	SPI_enuClk_2=0,
	SPI_enuClk_4,
	SPI_enuClk_8,
	SPI_enuClk_16,
	SPI_enuClk_32,
	SPI_enuClk_64,
	SPI_enuClk_128
	
}SPI_tenuClkRatePre;


/********************************/
/*SPI_enuInit Function
  Input: Void
  Output: SPI_tenuErrorStatus to report error*/
/******************************/
SPI_tenuErrorStatus SPI_enuInit(void);

/********************************/
/* SPI_enuSendAsyncByte Function
  Input:  SPI_u8SendByteValue
  Output:  SPI_tenuErrorStatus to report error*/
/******************************/
 SPI_tenuErrorStatus  SPI_enuSendAsyncByte(u8  SPI_u8SendByteValue);

/********************************/
/* SPI_u8SendByteValue Function
  Input:  SPI_u8ByteValue , pointer SPI_u8RecByteValue
  Output:  SPI_tenuErrorStatus to report error*/
/******************************/
 SPI_tenuErrorStatus  SPI_enuTranseiveSyncByte(u8  SPI_u8SendByteValue, u8 * SPI_u8RecByteValue);


/********************************/
/* SPI_enuSetCallBack Function
  Input: Cpy_CallBackPtr pointer to function
  Output:  SPI_tenuErrorStatus to report error*/
/******************************/
 SPI_tenuErrorStatus  SPI_enuSetCallBack( void(*Cpy_CallBackPtr)(void));





#endif /* SPI_H_ */