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

	#define ANJING_DISABLE_MSVC_4127_WARNING __pragma(warning(push)) __pragma(warning(disable:4127))
	#define ANJING_MSVC_WARNING_POP __pragma(warning(pop))

	#define ANJING_MULTI_LINE_MACRO_END \
		ANJING_DISABLE_MSVC_4127_WARNING\
		} while(0) \
		ANJING_MSVC_WARNING_POP
#else
	
	#define ANJING_DISABLE_MSVC_4127_WARNING	
	#define ANJING_MSVC_WARNING_POP

	#define ANJING_MULTI_LINE_MACRO_END }while(0)
#endif

// The following log macro has runtime check in it. why ? so that the compiler will always check that 
// the logging code is valid. Optimizer will remove it anyway when ANJING_LOG_TEST is 0.
// the do-while code ensure that this is a full statement so that it could be safely used in if else without curly braces.
// more info here : http://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing/1644898#1644898
// You also need to include <iostream> to use these functions
#define ANJING_LOG_TO_OUT(message, out)\
	ANJING_MULTI_LINE_MACRO_BEGIN\
		ANJING_DISABLE_MSVC_4127_WARNING\
		if (ANJING_LOG_TEST == 1){\
			if(ANJING_SHOW_LOG_INVOKE_LOCATION == 1)\
			{\
				out << message << " (log invoked from : " << __FILE__ << ":" << __LINE__ <<  ")" << std::endl;\
			}\
			else\
			{\
				out << message << std::endl;\
			}\
		}\
		ANJING_MSVC_WARNING_POP\
	ANJING_MULTI_LINE_MACRO_END

#define ANJING_LOG(message)\
	ANJING_LOG_TO_OUT(message, std::cout)

#define ANJING_LOGE(message)\
	ANJING_LOG_TO_OUT(message, std::cerr)

#define ANJING_LOGF(format, ...)\
	ANJING_MULTI_LINE_MACRO_BEGIN\
		ANJING_DISABLE_MSVC_4127_WARNING\
		if (ANJING_LOG_TEST == 1){\
			anjing::Log(__FILE__, __LINE__, format, ## __VA_ARGS__);\
		}\
		ANJING_MSVC_WARNING_POP\
	ANJING_MULTI_LINE_MACRO_END

//in wide char
#define ANJING_LOGW(message)\
	ANJING_LOG_TO_OUT(message, std::wcout)