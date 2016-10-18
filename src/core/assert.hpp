#pragma once

// for now, we simply define ANJING_ASSERT to be standard's assert 
#include <cassert>
#ifdef ANJING_DEBUG
	#define ANJING_ASSERT(exp) assert(exp)
#else
	#define ANJING_ASSERT(exp) ((void) 0)
#endif

