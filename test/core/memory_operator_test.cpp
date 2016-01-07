// Test memory manager operator overload

#ifndef ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE
#define ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE
#endif

#include "core/memory_operator.hpp"
#include "core/memory_manager.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;

// this class automatically cleans all our memory allocations during the test
class MemoryOperatorTest : public ::testing::Test
{
protected:

	virtual void TearDown() override
	{
		::testing::Test::TearDown();		
		MemoryManager::GetInstance().Clean();
	}
};

TEST_F(MemoryOperatorTest, NewFileLineCheck)
{
	int a_allocation_line = __LINE__ + 1;
	int* a = Anew int;

	AllocInfo* alloc_info = MemoryManager::GetAllocInfo(a);
	EXPECT_EQ(strcmp(alloc_info->filename, __FILE__), 0);
	EXPECT_EQ(alloc_info->line, a_allocation_line);
}

TEST_F(MemoryOperatorTest, NewArrFileLineCheck)
{
	int arr_allocation_line = __LINE__ + 1;
	int* arr = Anew int[10];

	AllocInfo* alloc_info = MemoryManager::GetAllocInfo(arr);
	EXPECT_EQ(strcmp(alloc_info->filename, __FILE__), 0);
	EXPECT_EQ(alloc_info->line, arr_allocation_line);
}

TEST_F(MemoryOperatorTest, NewDeleteCheck)
{
	int* a = Anew int;	

	EXPECT_GT(MemoryManager::GetInstance().GetTotalMemoryAllocations(), 0);
	
	Adelete(a);

	EXPECT_EQ(MemoryManager::GetInstance().GetTotalMemoryAllocations(), 0);
}

TEST_F(MemoryOperatorTest, NewDeleteArrCheck)
{
	char* a = Anew char[10];

	EXPECT_GT(MemoryManager::GetInstance().GetTotalMemoryAllocations(), 0);

	AdeleteArr(a);

	EXPECT_EQ(MemoryManager::GetInstance().GetTotalMemoryAllocations(), 0);
}
