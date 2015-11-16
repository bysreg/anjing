#pragma once

// for MSVC
#ifdef _DEBUG
	#define MYAPP_DEBUG
#endif 

#ifdef MYAPP_DEBUG
	#define ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE
#endif

#include "core/memory_operator.hpp"