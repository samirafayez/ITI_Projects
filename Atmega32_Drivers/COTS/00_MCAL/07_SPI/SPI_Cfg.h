/*
 * SPI_Cfg.h
 *
 * Created: 4/4/2023 3:05:52 PM
 *  Author: HP
 */ 
#ifndef SPI_CFG_H_
#define SPI_CFG_H_


typedef struct
{
SPI_tenuSPIDataOrder SPI_enuSPIDataOrder;
SPI_tenuMasterSlaveSel SPI_enuMasterSlaveSel;
SPI_tenuClkPolarity SPI_enuClkPolarity;
SPI_tenuClkPhase SPI_enuClkPhase;
SPI_tenuClkRatePre SPI_enuClkRatePre;
	
}SPI_tstrCfg;




#endif /* SPI_CFG_H_ */