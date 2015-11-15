#pragma once

#include <iostream>

//MACROS : 
//ANJING_ENABLE_LOG
//ANJING_LOG_TEST
//ANJING_SHOW_LOG_INVOKE_LOCATION

namespace anjing {
	void Log(const char* filename, int line, const char* format, ...);
}

#define ANJING_ENABLE_LOG // turn this off to disable logging

#ifdef ANJING_ENABLE_LOG
#define ANJING_LOG_TEST 1
#define ANJING_SHOW_LOG_INVOKE_LOCATION 0 // change to 1 to show where the ANJING_LOG or ANJING_LOGW is invoked
#else
#define ANJING_LOG_TEST 0
#define ANJING_SHOW_LOG_INVOKE_LOCATION 0
#endif

// the following log macro has runtime check in it. why ? so that the compiler will always check that 
// the logging code is valid. Optimizer will remove it anyway when ANJING_LOG_TEST is 0.
// the do-while code ensure that this is a full statement so that it could be safely used in if else without curly braces.
// more info here : http://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing/1644898#1644898
#define ANJING_LOG(message)\
	do {\
		if (ANJING_LOG_TEST){\
			if(ANJING_SHOW_LOG_INVOKE_LOCATION)\
			{\
				std::cout << message << " (log invoked from : " << __FILE__ << ":" << __LINE__ <<  ")" << std::endl;\
			}\
			else\
			{\
					std::cout << message << std::endl;\
			}\
		}\
	} while (0)

#define ANJING_LOGF(format, ...)\
	do { if (ANJING_LOG_TEST) anjing::Log(__FILE__, __LINE__, format, ## __VA_ARGS__); } while (0)

//in wide char
#define ANJING_LOGW(message)\
	do {\
		if (ANJING_LOG_TEST)\
		{\
			if (ANJING_SHOW_LOG_INVOKE_LOCATION)\
			{\
				std::wcout << message << " (log invoked from : " << __FILE__ << ":" << __LINE__ << ")" << std::endl;\
			}\
			else\
			{\
				std::wcout << message << " (log invoked from : " << __FILE__ << ":" << __LINE__ << ")" << std::endl;\
			}\
		}\
	} while (0)
