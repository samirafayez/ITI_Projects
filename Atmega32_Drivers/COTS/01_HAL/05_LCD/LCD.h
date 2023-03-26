/*
 * LCD.h
 *
 * Created: 2/11/2023 4:31:50 AM
 *  Author: HP
 */ 


#ifndef LCD_H_
#define LCD_H_


typedef enum
{
LCD_enuOk=0,
LCD_enuNotOk,
LCD_enuNullPtr
}LCD_enuErrorStatus;


LCD_enuErrorStatus LCD_vidInit(void);
LCD_enuErrorStatus LCD_enuSendData (u8 Copy_u8Data);
LCD_enuErrorStatus LCD_enuSendCommand (u8 Copy_u8Command);
LCD_enuErrorStatus LCD_enuGotoXY (u8 Copy_u8XPos, u8 Copy_u8YPos);
LCD_enuErrorStatus LCD_enuWriteSpecialPattern (u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos);

LCD_enuErrorStatus LCD_enuWriteString (char* Add_pchString);
LCD_enuErrorStatus LCD_enuWriteNumber (u16 Copy_u16Number);
LCD_enuErrorStatus LCD_enuClearScreen(void);
LCD_enuErrorStatus LCD_enuReturntohome(void);



#endif /* LCD_H_ */