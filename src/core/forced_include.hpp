#pragma once

#ifdef ANJING_DEBUG
	#define ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE
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

#include "core/types.hpp"
#include "core/memory_operator.hpp"
