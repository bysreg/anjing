#include "math/tvec3.hpp"

#include <gtest/gtest.h>

using namespace anjing::math;

TEST(TVec3Test, ConstructionCheck)
{
	TVec3<float> test;
	TVec3<int> test2;
	TVec3<double> test3(1, 2, 3);

	EXPECT_EQ(test.x, 0); EXPECT_EQ(test.y, 0); EXPECT_EQ(test.z, 0);
	EXPECT_EQ(test2.x, 0); EXPECT_EQ(test2.y, 0); EXPECT_EQ(test2.z, 0);
	EXPECT_EQ(test3.x, 1); EXPECT_EQ(test3.y, 2); EXPECT_EQ(test3.z, 3);
}

TEST(TVec3Test, AssignmentCheck)
{
	Vec3 test = Vec3(1, 2, 3);

	EXPECT_EQ(test.x, 1); EXPECT_EQ(test.y, 2); EXPECT_EQ(test.z, 3);
}