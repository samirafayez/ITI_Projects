/*
 * LCD_Cfg.c
 *
 *  Created on: Mar 28, 2023
 *      Author: HP
 */

#include "02_LCD/LCD_Cfg.h"
#include "01_GPIO/GPIO.h"



const LCD_tstrCfg LCD_strCfg =
{
		.LCD_tstrOperation = {
				.LCD_enuLinesNumber = LCD_enuTwoLines,
				.LCD_enuFontCfg = LCD_5x8Dots,
				.LCD_strBacklight = LCD_Enabled,
				.LCD_strCursor = LCD_Disabled,
				.LCD_strBlinkingCursor = LCD_Disabled

		},

		.LCD_tstrPins = {
				.LCD_RSPin.LCD_Port = GPIO_PORTB,
				.LCD_RSPin.LCD_Pin = GPIO_PIN_1,
				.LCD_RWPin.LCD_Port = GPIO_PORTB,
				.LCD_RWPin.LCD_Pin = GPIO_PIN_2,
				.LCD_EnablePin.LCD_Port = GPIO_PORTB,
				.LCD_EnablePin.LCD_Pin = GPIO_PIN_3,
				.LCD_DataPins[0].LCD_Port = GPIO_PORTA,
				.LCD_DataPins[0].LCD_Pin = GPIO_PIN_0,
				.LCD_DataPins[1].LCD_Port = GPIO_PORTA,
				.LCD_DataPins[1].LCD_Pin = GPIO_PIN_1,
				.LCD_DataPins[2].LCD_Port = GPIO_PORTA,
				.LCD_DataPins[2].LCD_Pin = GPIO_PIN_2,
				.LCD_DataPins[3].LCD_Port = GPIO_PORTA,
				.LCD_DataPins[3].LCD_Pin = GPIO_PIN_3,
				.LCD_DataPins[4].LCD_Port = GPIO_PORTA,
				.LCD_DataPins[4].LCD_Pin = GPIO_PIN_4,
				.LCD_DataPins[5].LCD_Port = GPIO_PORTA,
				.LCD_DataPins[5].LCD_Pin = GPIO_PIN_5,
				.LCD_DataPins[6].LCD_Port = GPIO_PORTA,
				.LCD_DataPins[6].LCD_Pin = GPIO_PIN_6,
				.LCD_DataPins[7].LCD_Port = GPIO_PORTA,
				.LCD_DataPins[7].LCD_Pin = GPIO_PIN_7
		}


};

