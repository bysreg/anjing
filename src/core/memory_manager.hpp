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
			
			// memory address returned from malloc
			void* mem;

			const char* filename;
			unsigned int line;

			// total memory allocated by MemoryManager for this allocation
			std::size_t mem_size; 
		};

		class MemoryManager
		{
		private:
			AllocInfo* free_list;
			AllocInfo* used_list;

			static const uint32 SENTINEL_CODE;

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

			///
			/// \brief Returns true if tail sentinel code in \a alloc_info memory layout is still intact
			///
			///
			bool CheckTailSentinel(const AllocInfo* alloc_info) const;

			///
			/// \brief Returns memory size of the metadata aside from the user requested memory allocation
			///
			/// MemoryManager, in order to put useful debugging information, will allocate more than 
			/// what the user actually requested. This function will return that extra allocation size.		
			///
			size_t GetMetadataMemorySize() const;

			///
			/// \brief Returns pointer to original allocated memory by MemoryManager
			///
			static void* GetAllocMem(void* actual_mem);

			///
			/// \brief Returns pointer to head sentinel provided the original allocated memory address
			///
			static void* GetHeadSentinel(void* alloc_mem);

			///
			/// \brief Returns pointer to tail sentinel provided the original allocated memory address
			///
			static void* GetTailSentinel(void* alloc_mem, size_t actual_mem_size);

			///
			/// \brief Returns pointer to the actual data provided the original allocated memory address
			///
			static void* GetActualData(void* alloc_mem);

		public:
			///
			/// \brief Return singleton instance of MemoryManager. 
			///
			static MemoryManager& GetInstance();

			///
			/// \brief Allocate memory with input of filename and line number of where the allocation is called
			///
			/// if \a ANJING_OVERRIDE_GLOBAL_NEW is defined, then operator new, and new[] will instead call this function
			void* Alloc(unsigned int numbytes, const char* filename, unsigned int line);

			///
			/// \brief Deallocate memory. Returns 1 if address is successfully deallocated
			///
			/// if \a address is nullptr, the function does nothing and returns 2
			/// if \a address is not allocated using Alloc(or by global operator new overrided by MemoryManager), it causes undefined behaviour
			/// this function does not change the value of \a address itself, hence it still points to the same (now invalid) location
			///
			/// Returns 2 if address is null pointer
			/// Returns 3 if tail sentinel code in address is not intact, indicating that there is memory overrun. Address is still deallocated.
			/// Returns 4 if head sentinel code in address is not intact, indicating that there is memory underflow or we are deleting
			///   something that is not allocated by MemoryManager
			///
			int Free(void* address, const char* filename, unsigned int line);

			///
			/// \brief List all the allocated memories by MemoryManager that haven't been deleted yet 
			///
			void Dump();			

			///
			/// \brief Removes all allocations. This will make MemoryManager state looks like it is just newly instantiated
			///
			/// Be careful to use this function. This will wipe out all allocations. We must make sure no other code has
			/// ownership of any of the allocations before performing this function. 
			void Clean();

			///
			/// \brief Returns total memory allocations. 
			///
			/// implementation detail : O(n) operation as this function iterates over all alocations.
			std::size_t GetTotalMemoryAllocations() const;

			///
			/// \brief Returns AllocInfo from the address. Adress is assumed to be allocated by MemoryManager
			///
			/// if \a address is nullptr, this function will return nullptr
			/// if \a address is not allocated using MemoryManager::All(or by global operator new overrided by MemoryManager), it causes undefined behaviour
			static AllocInfo* GetAllocInfo(void* address);
		};

	}
}