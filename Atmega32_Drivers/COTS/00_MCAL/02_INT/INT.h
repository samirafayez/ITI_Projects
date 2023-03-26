/*
 * INT.h
 *
 * Created: 1/26/2023 8:44:02 PM
 *  Author: HP
 */ 

#ifndef INT_H_
#define INT_H_


#define INT_0 0
#define INT_1 1
#define INT_2 2


typedef enum{

	INT_enuOK = 0,
	INT_enuNotOK ,
	INT_enuNullPtr
}INT_tenuErrorStatus;



/*typedef enum{
	INT_enuInt0=0, //PD2
	INT_enuInt1,   //PD3
	INT_enuInt2,    //PB2
	INT_enuIntPinsNumber 
}INT_tenuPins;*/




/********************************/
/*INT Init Function
  Input: INT pin to configure
  Output: INT_tenuErrorStatus to report error*/
/******************************/
INT_tenuErrorStatus INT_Init(void);


/********************************/
/*INT_Enable Function
  Input: INT pin to enable
  Output: INT_tenuErrorStatus to report error*/
/******************************/
INT_tenuErrorStatus INT_Enable(u8 Cpy_u8NumberPin);

/********************************/
/*INT_Disable Function
  Input: INT pin to disable
  Output: INT_tenuErrorStatus to report error*/
/******************************/
INT_tenuErrorStatus INT_Disable(u8 Cpy_u8NumberPin);



/********************************/
/*SetCallback Function
  Input: Pointer to Function
  Output: INT_tenuErrorStatus to report error 
  */
/******************************/
  
INT_tenuErrorStatus INT_SetCallback(u8 Cpy_u8INTPinNumber,void(*CpyFuncPtr)(void));




#endif /* INT_H_ */