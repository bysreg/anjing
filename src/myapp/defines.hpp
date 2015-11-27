#pragma once

#ifdef ANJING_DEBUG
	#define MYAPP_DEBUG
#endif 

#ifdef MYAPP_DEBUG
	#define ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE // replace Anew and Adelete macro with the two parameter __FILE__ and __LINE__ version
#endif

#include "core/memory_operator.hpp"