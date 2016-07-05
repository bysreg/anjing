#pragma once

#ifdef ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE
	#include <cstddef>
	#include <new>

	void* operator new (std::size_t size, const char* file, int line);
	void* operator new[](std::size_t size, const char* file, int line);
	void operator delete (void* p, const char* file, int line);
	void operator delete[](void* p, const char* file, int line);
	
	namespace anjing
	{
		namespace core
		{
			template<typename T>
			void Destroy(T* obj, const char* filename, unsigned int line)
			{
				obj->~T();
				operator delete(obj, filename, line);
			}

			template<typename T>
			void DestroyArr(T* obj, const char* filename, unsigned int line)
			{
				obj->~T();
				operator delete[](obj, filename, line);
			}
		}
	}

	#define Anew new(__FILE__, __LINE__)
	#define Adelete(M) anjing::core::Destroy(M, __FILE__, __LINE__)			
	#define AdeleteArr(M) anjing::core::DestroyArr(M, __FILE__, __LINE__)

#else
	
	#define Anew new
	#define Adelete(M) delete M
	#define AdeleteArr(M) delete[] M

#endif

