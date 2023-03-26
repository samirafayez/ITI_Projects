/*
 * INT_Cfg.h
 *
 * Created: 1/26/2023 8:12:21 PM
 *  Author: HP
 */ 


#ifndef INT_CFG_H_
#define INT_CFG_H_

#define LOW_LEVEL 0
#define LOGICAL_CHANGE 1
#define FALLING_EDGE 2
#define RISING_EDGE 3


#define INT_Enabled 1
#define INT_Disabled 0

typedef struct{
	u8 INT_State;
	u8 INT_Type;
}INT_tstrPinCfg_t;



/*
 *  Configure the EXT_INT pins
 *	LOW_LEVEL
 *	LOGICAL_CHANGE
 *	FALLING_EDGE 
 *	RISING_EDGE 
 *
 *
 *	Except for INT2 use:
 *	FALLING_EDGE 
 *  RISING_EDGE 
 *  >> ONLY
 *
 */


/*
 *  Configure the EXT_INT pins
 *	
 *	INT_Enabled
 *	INT_Disabled
 *
 */

const INT_tstrPinCfg_t INT_strPinCfg[3]= {
	/*INT0  >> PD2*/{INT_Enabled,RISING_EDGE},
	/*INT1  >> PD3*/{INT_Enabled,RISING_EDGE}, 
	/*INT2  >> PB2*/{INT_Disabled,RISING_EDGE}  //Rising edge and falling edge only
	};
		
#endif /* INT_CFG_H_ */