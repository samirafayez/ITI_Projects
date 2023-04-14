/*
 * Log.h
 *
 *  Created on: Feb 1, 2023
 *      Author: HP
 */

#ifndef LOG_H_
#define LOG_H_

typedef enum{
Log_tenuOk,
Log_tenuNotOk,
Log_tenu_NullPtr
}Log_tenuErrState;


typedef enum{
Console=0,
File,
Both
}Channel;



Log_tenuErrState Log_Init(Channel Copy_u8Channel, FILE * Add_pfileFileName);

Log_tenuErrState Log_Print(const char *fmt, ...);

#endif /* LOG_H_ */
