/*
 * test.c
 *
 *  Created on: Jan 5, 2023
 *      Author: HP
 */
#include<stdio.h>
#include<stdarg.h>
#include "Std_Types.h"
#include "Log.h"

FILE * Fptr;
Channel channel;

Log_tenuErrState Log_Init(Channel Copy_u8Channel, FILE * Add_pfileFileName)
{


	Fptr = Add_pfileFileName;
	Log_tenuErrState state = Log_tenuOk;
	if (Copy_u8Channel == Console)
	{
		channel = Console;
	}
	else if(Copy_u8Channel == File)
	{
		channel = File;
	}
	else if(Copy_u8Channel == Both)
	{
		channel = Both;
	}
	else
	{
		state = Log_tenuNotOk;
	}

	return state;
}

Log_tenuErrState Log_Print(const char *fmt, ...)
{

	Log_tenuErrState state = Log_tenuOk;
	va_list args;
	va_start(args, fmt);

	if(channel == Console)
	{
		vprintf(fmt,args);
	}
	else if (channel == File)
	{
		fprintf(Fptr,fmt);
	}
	else if(channel == Both)
	{
		vprintf(fmt,args);
		fprintf(Fptr,fmt);
		//vfprintf(Fptr,fmt,args);
	}
	else
	{
		state = Log_tenuNotOk;
	}

	va_end(args);

	return state;
}


int main(void)
{


	Log_Init(Both,Fptr);
	Fptr = fopen("text.txt","w");
	if(Fptr == NULL)
	{
		printf("Error while opening the file!!");
	}
	Log_Print("Hello World %d,%d",10,47);
	fclose(Fptr);
	return 0;
}

