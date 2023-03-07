/*
 * LOG.hpp
 *
 *  Created on: Mar 6, 2023
 *      Author: HP
 */

#ifndef LOG_HPP_
#define LOG_HPP_


#include<string>







typedef enum
{
lOff=0,
lError,
lWarn,
lInfo,
lDebug
}LogLevel;


typedef enum{
mFile=0,
mConsole,
mRemote
}LogMode;


class String{
public:
	int log_number;
	std::string appId;
	String(std::string appId);

};


class Logger{

private:
	static LogLevel log_level;
	static LogMode log_mode;
	static std::string AppId;
	//static int log_number;
	static const char* filepath;




public:
	static void CppLogger(String& app, LogLevel logLevel, LogMode logMode,const char* mssg);
	static void SetLogLevel(std::string appId, LogLevel logLevel);
	static void SetLogMode(std::string appId, LogMode logMode);

};







#endif /* LOG_HPP_ */
