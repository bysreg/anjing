#pragma once

// for now, we simply define ANJING_ASSERT to be standard's assert 
#include <cassert>
#ifdef ANJING_DEBUG && ANJING_WINDOWS
// TODO: not yet implemented
#define ANJING_ASSERT(exp) 
#endif

