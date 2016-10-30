#pragma once

#if defined(ANJING_DEBUG) && !defined(ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE)
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

#ifdef __linux__
// we are using OpenGL 3.0 because travis CI does not support newer OpenGL version
#define ANJING_OPENGL_VERSION 300
#define ANJING_OPENGL_MAJOR_VERSION 3
#define ANJING_OPENGL_MINOR_VERSION 0
#else
#define ANJING_OPENGL_VERSION 330
#define ANJING_OPENGL_MAJOR_VERSION 3
#define ANJING_OPENGL_MINOR_VERSION 3
#endif

#include "core/types.hpp"
#include "core/memory_operator.hpp"
