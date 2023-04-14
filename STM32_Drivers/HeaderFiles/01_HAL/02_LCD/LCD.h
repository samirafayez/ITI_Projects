/*
 * LCD.h
 *
 *  Created on: Mar 28, 2023
 *      Author: HP
 */

#ifndef LCD_H_
#define LCD_H_






typedef enum{

	LCD_enuOk=0,
	LCD_enuNotOk,
	LCD_enuProcessing,
	LCD_enuBusy

}LCD_tenuErrorStatus;




//LCD_tenuErrorStatus LCD_enuInit(void);
LCD_tenuErrorStatus LCD_enuSendData (u8 Copy_u8Data);
LCD_tenuErrorStatus LCD_enuSendCommand (u8 Copy_u8Command);
LCD_tenuErrorStatus LCD_enuGotoXY (u8 Copy_u8XPos, u8 Copy_u8YPos);
LCD_tenuErrorStatus LCD_enuWriteSpecialPattern (u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos);

LCD_tenuErrorStatus LCD_enuWriteString (char* Add_pchString);
LCD_tenuErrorStatus LCD_enuWriteNumber (u16 Copy_u16Number);
LCD_tenuErrorStatus LCD_enuClearScreen(void);
void LCD_vidTask(void);


#endif /* LCD_H_ */
