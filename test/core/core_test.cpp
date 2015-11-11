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

	virtual void TearDown()
	{
		// we need to clean down memory manager

	}
};

TEST(CoreTest, Singleton)
{

	MemoryManager& mm = MemoryManager::GetInstance();	
	MemoryManager& mm2 = MemoryManager::GetInstance();
	EXPECT_EQ(&mm2, &mm);

}

TEST(CoreTest, AllocNormal)
{
	MemoryManager& mm = MemoryManager::GetInstance();
	char filename[] = "test";
	int line = 12;
	
	void* alloc_mem = mm.Alloc(sizeof(TestClass), filename, line);
	
	EXPECT_NE(alloc_mem, nullptr);
	
	// get the AllocInfo address
	AllocInfo* alloc_info = (AllocInfo*) ((void**) (((char*) alloc_mem) - sizeof(AllocInfo*)))[0];
	EXPECT_NE(alloc_info, nullptr);
	
	EXPECT_EQ(strcmp(alloc_info->filename, filename), 0);
	EXPECT_EQ(alloc_info->line, line);
	EXPECT_GT(alloc_info->mem_size, 0);
	EXPECT_EQ((char*)alloc_info->mem + sizeof(AllocInfo*), alloc_mem);
}

TEST(CoreTest, DeallocNormal)
{
	MemoryManager& mm = MemoryManager::GetInstance();
	char filename[] = "test";
	int line = 12;

	void* alloc_mem = mm.Alloc(sizeof(TestClass), filename, line);

	mm.Free(alloc_mem);
}