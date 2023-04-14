/*
 * Scheduler_Cfg.c
 *
 *  Created on: Mar 26, 2023
 *      Author: HP
 */


#include "00_Scheduler/Scheduler_Cfg.h"


//extern void App1(void);
//extern void App2(void);
//extern void Switch(void);
extern void PUSHBUTTON_enuPUSHBUTTON_Read(void);
extern void LCD_vidTask(void);

const Scheduler_tsrRunnableInfo Scheduler_strRunnableInfo[Max_TasksNumber] =
{

		[0] =
		{
				.Name = "Switch_Read",
				.CallBackPtrFunc = PUSHBUTTON_enuPUSHBUTTON_Read,
				.Period_ms = 6,
				.Start_Delay = 1

		},

		/*[1] =
		{
				.Name = "BlinkingLed1",
				.CallBackPtrFunc = App1,
				.Period_ms = 500,
				.Start_Delay = 0

		},

		[2] =
		{
				.Name = "BlinkingLed2",
				.CallBackPtrFunc = App2,
				.Period_ms = 1000,
				.Start_Delay = 0

		},

		[3] =
		{
				.Name = "Switch",
				.CallBackPtrFunc = Switch,
				.Period_ms = 20,
				.Start_Delay = 0

		},*/

		[1] =
		{
				.Name = "LCD",
				.CallBackPtrFunc = LCD_vidTask,
				.Period_ms = 8,
				.Start_Delay = 30
		}


};
