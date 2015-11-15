#pragma once

#include <cstddef>

namespace anjing
{
	namespace core
	{

		struct AllocInfo
		{
			AllocInfo* prev;
			AllocInfo* next;						
			void* mem;
			char* filename;
			unsigned int line;			
			std::size_t mem_size; // total memory allocated by MemoryManager for this allocation
		};

		class MemoryManager
		{
		private:
			AllocInfo* free_list;
			AllocInfo* used_list;

			MemoryManager();
			~MemoryManager();
			
			MemoryManager(const MemoryManager&) = delete;
			void operator=(const MemoryManager&) = delete;

			///
			/// \brief Detach one AllocInfo from the free_list
			///
			AllocInfo* GetFreeAllocInfo();

			///
			/// \brief Remove \a used_alloc_info from used_list and attach it to free_list
			///
			/// \a used_alloc_info is assumed to be in used_list
			void RemoveUsedAllocInfo(AllocInfo* used_alloc_info);

		public:
			///
			/// \brief Return singleton instance of MemoryManager. 
			///
			static MemoryManager& GetInstance();

			///
			/// \brief Allocate memory with input of filename and line number of where the allocation is called
			///
			/// if \a ANJING_OVERRIDE_GLOBAL_NEW is defined, then operator new, and new[] will instead call this function
			void* Alloc(unsigned int numbytes, char* filename, unsigned int line);

			///
			/// \brief Deallocate memory
			///
			/// if \a address is nullptr, the function does nothing
			/// if \a address is not allocated using Alloc(or by global operator new overrided by MemoryManager), it causes undefined behaviour
			/// this function does not change the value of \a address itself, hence it still points to the same (now invalid) location
			///
			void Free(void* address);

			///
			/// \brief List all the allocated memories that haven't deleted yet 
			///
			void Dump();			

			///
			/// \brief Removes all allocations. This will make MemoryManager state looks like it is just newly instantiated
			///
			void Clean();

			///
			/// \brief Returns total memory allocations. 
			///
			/// implementation detail : O(n) operation as this function iterates over all alocations.
			std::size_t GetTotalMemoryAllocations();

			///
			/// \brief Returns AllocInfo from the address. Adress is assumed to be allocated by MemoryManager
			///
			/// if \a address is nullptr, this function will return nullptr
			/// if \a address is not allocated using MemoryManager::All(or by global operator new overrided by MemoryManager), it causes undefined behaviour
			static AllocInfo* GetAllocInfo(void* address);
		};

	}
}