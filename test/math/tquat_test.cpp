#include "math/tquat.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace anjing::core;
using namespace anjing::math;

TEST(TQuatfTest, ConstructionCheck)
{
	Quatf q;

	EXPECT_EQ(1, q.w);
	EXPECT_EQ(0, q.x);
	EXPECT_EQ(0, q.y);
	EXPECT_EQ(0, q.z);
}

TEST(TQuatfTest, IdentityCheck)
{
	Quatf q;
	q.SetAsIdentity();

	EXPECT_EQ(1, q.w);
	EXPECT_EQ(0, q.x);
	EXPECT_EQ(0, q.y);
	EXPECT_EQ(0, q.z);
}

TEST(TQuatfTest, PrintCheck)
{
	Quatf q;

	std::cout << q << std::endl;
}