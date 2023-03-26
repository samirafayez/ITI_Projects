/*
 * GBL_INT.h
 *
 * Created: 2/1/2023 3:07:33 PM
 *  Author: HP
 */ 


#ifndef GBL_INT_H_
#define GBL_INT_H_


typedef enum{

	GBL_INT_enuOK = 0,
	GBL_INT_enuNotOK ,
	GBL_INT_enuNullPtr
}GBL_INT_tenuErrorStatus;



/********************************/
/*INT_GlobalEnable Function
  Input: Void
  Output: INT_tenuErrorStatus to report error*/
  /******************************/
GBL_INT_tenuErrorStatus INT_GlobalEnable(void);


/********************************/
/*INT_GlobalDisable Function
  Input: Void
  Output: INT_tenuErrorStatus to report error*/
  /******************************/
GBL_INT_tenuErrorStatus INT_GlobalDisable(void);



#endif /* GBL_INT_H_ */