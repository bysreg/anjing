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

#define ANJING_MULTI_LINE_MACRO_BEGIN do {

#ifdef _MSC_VER
#define ANJING_MULTI_LINE_MACRO_END \
	__pragma(warning(push)) \
	__pragma(warning(disable:4127)) \
	} while(0) \
	__pragma(warning(pop))
#else
	#define ANJING_MULTI_LINE_MACRO_END }while(0)
#endif

// the following log macro has runtime check in it. why ? so that the compiler will always check that 
// the logging code is valid. Optimizer will remove it anyway when ANJING_LOG_TEST is 0.
// the do-while code ensure that this is a full statement so that it could be safely used in if else without curly braces.
// more info here : http://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing/1644898#1644898
#define ANJING_LOG(message)\
	ANJING_MULTI_LINE_MACRO_BEGIN\
		__pragma(warning(push)) \
		__pragma(warning(disable:4127)) \
		if (ANJING_LOG_TEST == 1){\
			if(ANJING_SHOW_LOG_INVOKE_LOCATION == 1)\
			{\
				std::cout << message << " (log invoked from : " << __FILE__ << ":" << __LINE__ <<  ")" << std::endl;\
			}\
			else\
			{\
				std::cout << message << std::endl;\
			}\
		}\
		__pragma(warning(pop))\
	ANJING_MULTI_LINE_MACRO_END

#define ANJING_LOGF(format, ...)\
	ANJING_MULTI_LINE_MACRO_BEGIN\
		__pragma(warning(push)) \
		__pragma(warning(disable:4127)) \
		if (ANJING_LOG_TEST == 1){\
			anjing::Log(__FILE__, __LINE__, format, ## __VA_ARGS__);\
		}\
		__pragma(warning(pop))\
	ANJING_MULTI_LINE_MACRO_END

//in wide char
#define ANJING_LOGW(message)\
	ANJING_MULTI_LINE_MACRO_BEGIN\
		__pragma(warning(push)) \
		__pragma(warning(disable:4127)) \
		if (ANJING_LOG_TEST == 1)\
		{\
			if (ANJING_SHOW_LOG_INVOKE_LOCATION == 1)\
			{\
				std::wcout << message << " (log invoked from : " << __FILE__ << ":" << __LINE__ << ")" << std::endl;\
			}\
			else\
			{\
				std::wcout << message << " (log invoked from : " << __FILE__ << ":" << __LINE__ << ")" << std::endl;\
			}\
		}\
		__pragma(warning(pop))\
	ANJING_MULTI_LINE_MACRO_END
