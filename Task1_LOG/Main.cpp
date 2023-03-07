/*
 * Main.cpp
 *
 *  Created on: Mar 6, 2023
 *      Author: HP
 */


#include"Log.hpp"



int main(void)
{


	String App1("App_3");
	Logger::CppLogger(App1,lError ,mConsole,"this is a Error");
	Logger::CppLogger(App1,lError ,mConsole,"Error");
	String App2("app_4");
	Logger::CppLogger(App2,lError ,mFile,"this is an Error");

	return 0;
}


