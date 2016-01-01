#include "core/util.hpp"

#include <string>

void anjing::core::CopyString(char* dest, size_t dest_size, const char* src, size_t count)
{
#ifdef _MSC_VER
	strncpy_s(dest, dest_size, src, count);
#else
	strcpy(dest, src, count);
#endif
}
