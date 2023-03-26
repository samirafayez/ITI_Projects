/*
 * SSEG.h
 *
 * Created: 1/20/2023 2:47:00 PM
 *  Author: HP
 */ 


#ifndef SSEG_H_
#define SSEG_H_


#define PORTA_REG 0
#define PORTB_REG 1
#define PORTC_REG 2
#define PORTD_REG 3



typedef enum{

SSEG_enuOK = 0,
SSEG_enuNotOK ,
SSEG_enuNullPtr
}SSEG_tenuErrorStatus;








/********************************/
/*SSEG Number Function
  Input: Port the Seven segment is connected to (ex. PORTA_REG) and Number you want to show on SevenSegment
  Output: ErrorStatus
  */
  /******************************/
SSEG_tenuErrorStatus SSEG_enuNumberShow(u8 SSEG_u8Port, u8 SSEG_u8Index);

/********************************/
/*SSEG off Function
  Input: Port connected to 7 Segment
  Output: ErrorStatus
  */
  /******************************/
SSEG_tenuErrorStatus SSEG_enuSSEGoff(u8 SSEG_u8Port);

/********************************/



#endif /* SSEG_H_ */