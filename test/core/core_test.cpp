#include "core/memory_manager.hpp"

#include <gtest/gtest.h>
//#include <string>

using namespace anjing;
using namespace anjing::core;
using namespace std;

class TestClass
{
	int foo;
};

class MemoryManagerTest : public ::testing::Test 
{
protected:

	char* filename;
	int line;

	virtual void SetUp()
	{
		::testing::Test::SetUp();		

		filename = new char[5];
		strcpy(filename, "test");
		line = 12;
	}

	virtual void TearDown()
	{
		::testing::Test::TearDown();

		// we need to clean down memory manager
		MemoryManager::GetInstance().Clean();

		delete filename;
	}	

	void* DoAllocation()
	{
		return MemoryManager::GetInstance().Alloc(sizeof(TestClass), filename, line);
	}
};

// test two call to MemoryManager::GetInstance() will both return the same object
TEST_F(MemoryManagerTest, Singleton)
{

	MemoryManager& mm = MemoryManager::GetInstance();	
	MemoryManager& mm2 = MemoryManager::GetInstance();
	EXPECT_EQ(&mm2, &mm);	
}

// test one allocation with MemoryManager. 
TEST_F(MemoryManagerTest, AllocNormal)
{
	MemoryManager& mm = MemoryManager::GetInstance();	
	
	void* alloc_mem = DoAllocation();

	EXPECT_NE(alloc_mem, nullptr);
	
	// get the AllocInfo address
	AllocInfo* alloc_info = MemoryManager::GetAllocInfo(alloc_mem);
	EXPECT_NE(alloc_info, nullptr);
	
	EXPECT_EQ(strcmp(alloc_info->filename, filename), 0);
	EXPECT_EQ(alloc_info->line, line);
	EXPECT_GT(alloc_info->mem_size, 0);	
	EXPECT_EQ((char*)alloc_info->mem + sizeof(AllocInfo*), alloc_mem);
	EXPECT_GT(mm.GetTotalMemoryAllocations(), 0);
	EXPECT_EQ(alloc_info->mem_size, mm.GetTotalMemoryAllocations());
	EXPECT_EQ(alloc_info->prev, nullptr);
	EXPECT_EQ(alloc_info->next, nullptr);
}

// test one allocation and one deallocation with MemoryManager
TEST_F(MemoryManagerTest, DeallocNormal)
{
	MemoryManager& mm = MemoryManager::GetInstance();	

	void* alloc_mem = DoAllocation();
	AllocInfo* allocinfo = mm.GetAllocInfo(alloc_mem);

	mm.Free(alloc_mem);

	EXPECT_EQ(mm.GetTotalMemoryAllocations(), 0);

	EXPECT_EQ(allocinfo->prev, nullptr);
	EXPECT_EQ(allocinfo->next, nullptr);
}

// test five allocations with MemoryManager
TEST_F(MemoryManagerTest, MultipleAlloc)
{
	MemoryManager& mm = MemoryManager::GetInstance();	
	void* allocations[5];
	size_t total_one_allocation_size = 0;
	
	for (int i = 0; i < 5; i++)
	{
		allocations[i] = DoAllocation();
	}

	total_one_allocation_size = MemoryManager::GetAllocInfo(allocations[0])->mem_size;
	
	EXPECT_GT(mm.GetTotalMemoryAllocations(), 0);
	EXPECT_EQ(mm.GetTotalMemoryAllocations(), total_one_allocation_size * 5);
}

// test deallocation on secondly allocated memory address
// this will test deleting AllocInfo element in the middle of the used_list
TEST_F(MemoryManagerTest, MultipleAllocDealloc)
{
	MemoryManager& mm = MemoryManager::GetInstance();	
	void* allocations[5];
	AllocInfo* allocinfos[5];
	size_t total_one_allocation_size = 0;

	allocations[0] = DoAllocation();
	allocinfos[0] = mm.GetAllocInfo(allocations[0]);
	total_one_allocation_size = allocinfos[0]->mem_size;
	
	allocations[1] = DoAllocation();
	allocinfos[1] = mm.GetAllocInfo(allocations[1]);
	allocations[2] = DoAllocation();
	allocinfos[2] = mm.GetAllocInfo(allocations[2]);

	mm.Free(allocations[1]);

	EXPECT_EQ(mm.GetTotalMemoryAllocations(), 2 * total_one_allocation_size);

	// the third allocation should now be the first element of the used_list
	EXPECT_EQ(mm.GetAllocInfo(allocations[2])->prev, nullptr);

	// the third allocation should now be linked to the first allocation
	EXPECT_EQ(allocinfos[2]->next, allocinfos[0]);
	EXPECT_EQ(allocinfos[0]->prev, allocinfos[2]);
}

//TEST_F()