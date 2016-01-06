#include "core/memory_manager.hpp"
#include "core/log.hpp"
#include "core/util.hpp"
#include "core/types.hpp"

#include <cstdlib>
#include <cstring>
#include <string>

using namespace anjing::core;

const uint32 SENTINEL_CODE = 0x12345678;

void reset_alloc_info(AllocInfo* alloc_info)
{
	alloc_info->prev = nullptr;
	alloc_info->next = nullptr;
	alloc_info->mem = nullptr;
	alloc_info->filename = nullptr;
	alloc_info->line = 0;
	alloc_info->mem_size = 0;
}

MemoryManager& MemoryManager::GetInstance()
{
	static MemoryManager instance;
	return instance;
}

MemoryManager::MemoryManager() : free_list(nullptr), used_list(nullptr)
{}

MemoryManager::~MemoryManager()
{}

void* MemoryManager::Alloc(unsigned int numbytes, const char* filename, unsigned int line)
{
	AllocInfo* alloc_info = GetFreeAllocInfo();
	
	// attached the alloc_info the used list
	if (used_list == nullptr)
	{
		used_list = alloc_info;
	}
	else
	{
		alloc_info->next = used_list;
		used_list->prev = alloc_info;
		used_list = alloc_info;
	}

	// allocate the actual requested memory. we are going to request more than the numbytes
	size_t allocated_mem_size = numbytes + GetMetadataMemorySize();
	void* allocated_mem = malloc(allocated_mem_size);
	void* actual_mem = AddOffsetToPointer(allocated_mem, sizeof(AllocInfo*));	
	
	// put the address of the allocinfo in the first bytes of the allocated_mem
	memcpy(allocated_mem, &alloc_info, sizeof(AllocInfo*));

	// put check code in the last bytes of the allocated_mem
	memcpy(AddOffsetToPointer(actual_mem, numbytes), &SENTINEL_CODE, sizeof(SENTINEL_CODE));

	alloc_info->mem = allocated_mem;
	alloc_info->filename = filename;
	alloc_info->line = line;
	alloc_info->mem_size = allocated_mem_size;

	return actual_mem;
}

int MemoryManager::Free(void* address, const char* filename, unsigned int line)
{
	if (address == nullptr)
		return 2;

	AllocInfo* alloc_info = GetAllocInfo(address);	
	int ret_code = 1;

	// before free, check whether the sentinel value is still intact
	bool is_memory_overrun = CheckSentinel(alloc_info) == false;
	if (is_memory_overrun)
	{
		std::string err_msg = "Memory overrun detected!! Allocated in " +
			std::string(alloc_info->filename) + " line " + std::to_string(alloc_info->line) +
			" and deleted in " + std::string(filename) + " line " + std::to_string(line);

		ANJING_LOGE(err_msg);
		ret_code = 3;
	}

	free(alloc_info->mem);
	RemoveUsedAllocInfo(alloc_info);
	return ret_code;
}

void MemoryManager::Dump()
{
	// walk over the used list
	AllocInfo* head = used_list;

	int index = 0;

	ANJING_LOG("\nStarting memory dump\n");

	while (head != nullptr)
	{
		ANJING_LOGF("%4d. 0x%p: %d bytes | %d req bytes (%s: %d)\n", index + 1, head->mem, head->mem_size, 
			head->mem_size - GetMetadataMemorySize(), head->filename, head->line);

		head = head->next;
		++index;
	}

	size_t total_memory_left = GetTotalMemoryAllocations();
	ANJING_LOGF("\nTotal memory not deleted : %d\n", total_memory_left);
	ANJING_LOG("---------------------------\n");
}

void MemoryManager::Clean()
{
	// remove all allocations in used_list	
	
	AllocInfo* head = used_list;
	AllocInfo* next;

	if (head != nullptr)
	{
		next = head->next;
		RemoveUsedAllocInfo(head);
		head = next;
	}

	// used_list now should be empty, now we delete all AllocInfo from free_list
	head = free_list;
	if (head != nullptr)
	{
		next = head->next;
		free(head);
		head = next;
	}

	used_list = nullptr;
	free_list = nullptr;
}

AllocInfo* MemoryManager::GetFreeAllocInfo()
{
	// check if there is any free alloc info 
	if (free_list != nullptr)
	{
		// detach the first element of free_list
		AllocInfo* ret = free_list;		

		free_list = free_list->next;
		if(free_list != nullptr)
			free_list->prev = nullptr;		

		ret->next = nullptr;
		return ret;
	}
	else
	{
		// nothing is free, we need to allocate some
		AllocInfo* alloc_info = static_cast<AllocInfo*>( malloc(sizeof(AllocInfo)));
		reset_alloc_info(alloc_info);
		return alloc_info;
	}
}

bool MemoryManager::CheckSentinel(const AllocInfo* alloc_info) const
{	
	char* cmem = static_cast<char*>(alloc_info->mem);
	cmem = cmem + alloc_info->mem_size - sizeof(SENTINEL_CODE);
	int diff = memcmp(cmem, &SENTINEL_CODE, sizeof(SENTINEL_CODE));

	return diff == 0;
}

size_t MemoryManager::GetMetadataMemorySize() const
{
	return sizeof(SENTINEL_CODE) + sizeof(AllocInfo*);
}

void MemoryManager::RemoveUsedAllocInfo(AllocInfo* used_alloc_info)
{
	// remove alloc_info from the used list
	if (used_alloc_info->prev != nullptr)
	{
		used_alloc_info->prev->next = used_alloc_info->next;
		
		if (used_alloc_info->next != nullptr)
		{
			used_alloc_info->next->prev = used_alloc_info->prev;
		}
	}
	else
	{
		used_list = used_list->next;

		if (used_list != nullptr)
		{			
			used_list->prev = nullptr;
		}			
	}

	reset_alloc_info(used_alloc_info);

	// and attach it to the free list
	if (free_list != nullptr)
	{
		free_list->prev = used_alloc_info;
		used_alloc_info->next = free_list;
		free_list = used_alloc_info;
	}
	else
	{
		free_list = used_alloc_info;
	}
}

size_t MemoryManager::GetTotalMemoryAllocations() const
{
	AllocInfo* head = used_list;
	size_t ret = 0;

	while (head != nullptr)
	{
		ret += head->mem_size;
		head = head->next;
	}

	return ret;
}

AllocInfo* MemoryManager::GetAllocInfo(void* address)
{
	if (address == nullptr)
		return nullptr;

	AllocInfo* alloc_info = *(static_cast<AllocInfo**>(AddOffsetToPointer(address, -sizeof(AllocInfo*))));
	return alloc_info;
}

void* operator new (std::size_t size, const char* file, int line)
{
	return MemoryManager::GetInstance().Alloc(size, file, line);
}

void* operator new[](std::size_t size, const char* file, int line)
{
	return MemoryManager::GetInstance().Alloc(size, file, line);
}

void operator delete (void* p, const char* file, int line)
{
	ANJING_UNUSED(file);
	ANJING_UNUSED(line);

	MemoryManager::GetInstance().Free(p, file, line);
}

void operator delete[](void* p, const char* file, int line)
{
	ANJING_UNUSED(file);
	ANJING_UNUSED(line);

	MemoryManager::GetInstance().Free(p, file, line);
}
