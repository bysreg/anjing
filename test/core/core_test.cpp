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

		delete filename; // this has to be called before MemoryManager cleans. Because operaetor new and delete might be override by MemoryManager

		// we need to clean down memory manager
		MemoryManager::GetInstance().Clean();
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

// test MemoryManager::Alloc
TEST_F(MemoryManagerTest, AllocNormal)
{
	void* alloc_mem = DoAllocation();

	EXPECT_NE(alloc_mem, nullptr);
}

// test MemoryManager::GetTotalMemoryAllocations
TEST_F(MemoryManagerTest, GetTotalMemoryAllocations)
{
	EXPECT_EQ(MemoryManager::GetInstance().GetTotalMemoryAllocations(), 0);

	void* alloc_mem = DoAllocation();

	// the memory allocated must be at least the size of the TestClass
	EXPECT_GE(MemoryManager::GetInstance().GetTotalMemoryAllocations(), sizeof(TestClass));
}

// test MemoryManager::GetAllocInfo
TEST_F(MemoryManagerTest, GetAllocInfo)
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

// test allocation & deallocation on this order : 
// 1) alloc, we name this id 0
// 2) alloc, we name this id 1
// 3) alloc, we name this id 2
// 4) free id 1
// 5) free id 2
// 6) alloc, we name this id 3
// 7) free id 3
// 8) free id 0
TEST_F(MemoryManagerTest, MultipleAllocDealloc1)
{
	MemoryManager& mm = MemoryManager::GetInstance();	
	void* allocations[5];
	AllocInfo* allocinfos[5];
	size_t total_one_allocation_size = 0;

	// allocate 3 memories
	allocations[0] = DoAllocation();
	allocinfos[0] = mm.GetAllocInfo(allocations[0]);
	total_one_allocation_size = allocinfos[0]->mem_size;	
	allocations[1] = DoAllocation();
	allocinfos[1] = mm.GetAllocInfo(allocations[1]);
	allocations[2] = DoAllocation();
	allocinfos[2] = mm.GetAllocInfo(allocations[2]);

	// remove (1)
	mm.Free(allocations[1]);

	EXPECT_EQ(mm.GetTotalMemoryAllocations(), 2 * total_one_allocation_size);

	// used_list layout : (2)<->(0)
	// free_list layout : (1)
	EXPECT_EQ(allocinfos[0]->prev, allocinfos[2]);
	EXPECT_EQ(allocinfos[0]->next, nullptr);	
	EXPECT_EQ(allocinfos[1]->prev, nullptr);
	EXPECT_EQ(allocinfos[1]->next, nullptr);
	EXPECT_EQ(allocinfos[2]->prev, nullptr);	
	EXPECT_EQ(allocinfos[2]->next, allocinfos[0]);		

	// remove (2)
	mm.Free(allocations[2]);
	
	// used_list layout : (0)
	// free_list layout : (2)<->(1)
	EXPECT_EQ(allocinfos[0]->prev, nullptr);
	EXPECT_EQ(allocinfos[0]->next, nullptr);
	EXPECT_EQ(allocinfos[1]->prev, allocinfos[2]);
	EXPECT_EQ(allocinfos[1]->next, nullptr);	
	EXPECT_EQ(allocinfos[2]->prev, nullptr);
	EXPECT_EQ(allocinfos[2]->next, allocinfos[1]);

	EXPECT_EQ(mm.GetTotalMemoryAllocations(),  total_one_allocation_size);

	// allocate (3)
	allocations[3] = DoAllocation();
	allocinfos[3] = mm.GetAllocInfo(allocations[3]);

	EXPECT_EQ(mm.GetTotalMemoryAllocations(), 2 * total_one_allocation_size);

	// used_list layout : (2)<->(0)
	// free_list layout : (1) 
	// note: (2) equals to (3)
	EXPECT_EQ(allocinfos[0]->prev, allocinfos[2]);
	EXPECT_EQ(allocinfos[0]->next, nullptr);
	EXPECT_EQ(allocinfos[1]->prev, nullptr);
	EXPECT_EQ(allocinfos[1]->next, nullptr);
	EXPECT_EQ(allocinfos[2]->prev, nullptr);
	EXPECT_EQ(allocinfos[2]->next, allocinfos[0]);
	EXPECT_EQ(allocinfos[3], allocinfos[2]);

	// remove (0) & (3) allocation
	mm.Free(allocations[0]);
	mm.Free(allocations[3]);

	EXPECT_EQ(mm.GetTotalMemoryAllocations(), 0);

	// used_list layout : --
	// free_list layout : (2)<->(0)<->(1) 
	// note: (2) equals to (3)
	EXPECT_EQ(allocinfos[0]->prev, allocinfos[2]);
	EXPECT_EQ(allocinfos[0]->next, allocinfos[1]);
	EXPECT_EQ(allocinfos[1]->prev, allocinfos[0]);
	EXPECT_EQ(allocinfos[1]->next, nullptr);
	EXPECT_EQ(allocinfos[2]->prev, nullptr);
	EXPECT_EQ(allocinfos[2]->next, allocinfos[0]);
	EXPECT_EQ(allocinfos[3], allocinfos[2]);
}

// test allocation & deallocation on this order : 
// 1) alloc, we name this id 0
// 2) alloc, we name this id 1
// 3) free id 1
// 4) free id 0
// 5) alloc 2
// 6) alloc 3
TEST_F(MemoryManagerTest, MultipleAllocDealloc2)
{
	MemoryManager& mm = MemoryManager::GetInstance();
	void* allocations[5];
	AllocInfo* allocinfos[5];
	size_t total_one_allocation_size = 0;

	// allocate 2 memories
	allocations[0] = DoAllocation();
	allocinfos[0] = mm.GetAllocInfo(allocations[0]);
	total_one_allocation_size = allocinfos[0]->mem_size;
	allocations[1] = DoAllocation();
	allocinfos[1] = mm.GetAllocInfo(allocations[1]);	

	// remove (1)
	mm.Free(allocations[1]);

	EXPECT_EQ(mm.GetTotalMemoryAllocations(), total_one_allocation_size);

	// used_list layout : (0)
	// free_list layout : (1)
	EXPECT_EQ(allocinfos[0]->prev, nullptr);
	EXPECT_EQ(allocinfos[0]->next, nullptr);
	EXPECT_EQ(allocinfos[1]->prev, nullptr);
	EXPECT_EQ(allocinfos[1]->next, nullptr);	

	// remove (0)
	mm.Free(allocations[0]);

	// used_list layout : --
	// free_list layout : (0)<->(1)
	EXPECT_EQ(allocinfos[0]->prev, nullptr);
	EXPECT_EQ(allocinfos[0]->next, allocinfos[1]);
	EXPECT_EQ(allocinfos[1]->prev, allocinfos[0]);
	EXPECT_EQ(allocinfos[1]->next, nullptr);	

	EXPECT_EQ(mm.GetTotalMemoryAllocations(), 0);

	DoAllocation();
	DoAllocation();
}