#include "math/tvec3.hpp"
#include "core/types.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;
using namespace anjing::math;

TEST(TVec3Test, ConstructionCheck)
{
	TVec3<float> test;
	TVec3<int32> test2;
	TVec3<double> test3(1, 2, 3);

	EXPECT_EQ(test.x, 0); EXPECT_EQ(test.y, 0); EXPECT_EQ(test.z, 0);
	EXPECT_EQ(test2.x, 0); EXPECT_EQ(test2.y, 0); EXPECT_EQ(test2.z, 0);
	EXPECT_EQ(test3.x, 1); EXPECT_EQ(test3.y, 2); EXPECT_EQ(test3.z, 3);
}

TEST(TVec3Test, xyzrgbstpCheck)
{
	Vec3 test(1, 2, 3);

	EXPECT_EQ(test.x, test.r); EXPECT_EQ(test.x, test.s);
	EXPECT_EQ(test.y, test.g); EXPECT_EQ(test.y, test.t);
	EXPECT_EQ(test.z, test.b); EXPECT_EQ(test.z, test.p);
}

TEST(TVec3Test, AssignmentCheck)
{
	Vec3 test = Vec3(1, 2, 3);

	EXPECT_EQ(test.x, 1); EXPECT_EQ(test.y, 2); EXPECT_EQ(test.z, 3);
}