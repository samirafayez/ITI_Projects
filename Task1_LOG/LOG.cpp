/*
 * LOG.cpp
 *
 *  Created on: Mar 6, 2023
 *      Author: HP
 */


#include "LOG.hpp"
#include<iostream>
#include<ctime>
#include<fstream>
#include <cstdarg>


std::string LEVEL;

String::String(std::string appId)
{
	this->appId = appId;
	this->log_number=0;
}

static void PrintTimeStamp(void)
{
	time_t now = time(0);
	tm * CurrentTime = localtime(&now);
	std::cout<<CurrentTime->tm_hour<<":"<< CurrentTime->tm_min << ":" <<CurrentTime->tm_sec;
}



LogLevel Logger::log_level = lOff;
LogMode Logger::log_mode = mConsole;
const char* Logger::filepath = "Log.txt";
//int Logger::log_number =0;
std::string Logger::AppId = "App_0";
int Log_Number =0;


void Logger::CppLogger( String& app, LogLevel logLevel, LogMode logMode,const char* mssg)
{

	AppId = app.appId;
	log_level = logLevel;
	log_mode = logMode;
	app.log_number++;
	Log_Number = app.log_number;
	if(logMode == mConsole)
	{
		std::cout<<" | ";
		PrintTimeStamp();
		if(logLevel <= log_level)
		{
			switch(logLevel)
			{
			case lOff:

				LEVEL = "lOff";
				std::cout<<" | "<< LEVEL<<" | "<< std::endl;
				break;
			case lError:
				LEVEL = "lError";
				std::cout<<" | "<< AppId << " | "<< Log_Number << " | "<< LEVEL<<" | "<< mssg <<" | "<< std::endl;
				break;
			case lWarn:
				LEVEL = "lWarn";
				std::cout<<" | "<< AppId << " | "<< Log_Number<< " | "<< LEVEL<<" | "<< mssg <<" | "<< std::endl;
				break;
			case lInfo:
				LEVEL = "lInfo";
				std::cout<<" | "<< AppId << " | "<< Log_Number<< " | "<< LEVEL<<" | "<< mssg <<" | "<< std::endl;
				break;
			case lDebug:
				LEVEL = "lDebug";
				std::cout<<" | "<< AppId << " | "<< Log_Number << " | "<< LEVEL<<" | "<< mssg <<" | "<< std::endl;
				break;
			}
		}
	}
	else if(logMode == mFile)
	{
		std::ofstream LOG_FILE(filepath);
		LOG_FILE<<" | ";
		time_t now = time(0);
		tm * CurrentTime = localtime(&now);
		LOG_FILE<<CurrentTime->tm_hour<<":"<< CurrentTime->tm_min << ":" <<CurrentTime->tm_sec;
		if(logLevel <= log_level)
		{
			switch(logLevel)
			{
			case lOff:

				LEVEL = "lOff";
				LOG_FILE<<" | "<< LEVEL<<" | "<< std::endl;
				break;
			case lError:
				LEVEL = "lError";
				LOG_FILE<<" | "<< AppId << " | "<< Log_Number << " | "<< LEVEL<<" | "<< mssg <<" | "<< std::endl;
				break;
			case lWarn:
				LEVEL = "lWarn";
				LOG_FILE<<" | "<< AppId << " | "<< Log_Number<< " | "<< LEVEL<<" | "<< mssg <<" | "<< std::endl;
				break;
			case lInfo:
				LEVEL = "lInfo";
				LOG_FILE<<" | "<< AppId << " | "<< Log_Number<< " | "<< LEVEL<<" | "<< mssg <<" | "<< std::endl;
				break;
			case lDebug:
				LEVEL = "lDebug";
				LOG_FILE<<" | "<< AppId << " | "<< Log_Number << " | "<< LEVEL<<" | "<< mssg <<" | "<< std::endl;
				break;
			}
		}

		LOG_FILE.close();
	}


}


void Logger::SetLogLevel(std::string appId, LogLevel logLevel)
{

	log_level = logLevel;
}


void Logger::SetLogMode(std::string appId, LogMode logMode)
{

	log_mode = logMode;
}



