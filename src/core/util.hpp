#pragma once

#include <cstddef>

#define ANJING_UNUSED(expr) (void)(expr)

namespace anjing
{
	namespace core
	{
		///
		/// \brief Essentially the same function as strcpy
		///
		/// This function will change into strcpy_s in windows and change to strcpy in other compilers
		/// Use this function instead of strcpy. This function is made mainly to avoid warning of
		/// 'unsafe' function in msvc. Should probably implement this function to actually behave
		/// like the C++11 extension standard of strncpy_s
		/// 
		void CopyString(char* dest, size_t dest_size, const char* src, size_t count);
	}
}