/*
 * LCD_Cfg.h
 *
 *  Created on: Mar 28, 2023
 *      Author: HP
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_


#include "std_defines.h"



#define LCD_DataPinsNumber 8

#define LCD_Disabled 0
#define LCD_Enabled  1


typedef enum{

	LCD_enuOneLine=0,
	LCD_enuTwoLines

}LCD_tenuLinesNumber;


typedef enum{

	LCD_5x8Dots=0,
	LCD_5x11Dots

}LCD_tenuFontCfg;

typedef struct{

	u8 LCD_Port;
	u8 LCD_Pin;

}LCD_tenuPinsCfg;



typedef struct{


	struct{

		LCD_tenuLinesNumber LCD_enuLinesNumber;
		LCD_tenuFontCfg LCD_enuFontCfg;
		u8 LCD_strBacklight : 1;
		u8 LCD_strCursor : 1;
		u8 LCD_strBlinkingCursor : 1;

	}LCD_tstrOperation;


	struct{

		LCD_tenuPinsCfg LCD_RSPin;
		LCD_tenuPinsCfg LCD_RWPin;
		LCD_tenuPinsCfg LCD_EnablePin;
		LCD_tenuPinsCfg LCD_DataPins[LCD_DataPinsNumber];

	}LCD_tstrPins;



}LCD_tstrCfg;



#endif /* LCD_CFG_H_ */
