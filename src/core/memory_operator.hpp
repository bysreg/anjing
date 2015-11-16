#pragma once

#ifdef ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE
	#include <cstddef>
	void* operator new (std::size_t size, const char* file, int line);
	void* operator new[](std::size_t size, const char* file, int line);
	void operator delete (void* p, const char* file, int line);
	void operator delete[](void* p, const char* file, int line);

	#define Anew new(__FILE__, __LINE__)
	#define Adelete(M) operator delete(M, __FILE__, __LINE__);
	
#else
	
	#define Anew new
	#define Adelete delete

#endif

