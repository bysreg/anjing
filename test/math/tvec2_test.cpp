#include "math/tvec2.hpp"
#include "core/types.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;
using namespace anjing::math;

TEST(TVec4Test, ConstructionCheck)
{
	TVec2<float> test;
	TVec2<int32> test2;
	TVec2<double> test3(1, 2);

	EXPECT_EQ(test.x, 0); EXPECT_EQ(test.y, 0);
	EXPECT_EQ(test2.x, 0); EXPECT_EQ(test2.y, 0);
	EXPECT_EQ(test3.x, 1); EXPECT_EQ(test3.y, 2);
}

TEST(TVec3Test, xyzrgbstpCheck)
{
	Vec2 test(1, 2);

	EXPECT_EQ(test.x, test.r); EXPECT_EQ(test.x, test.s);
	EXPECT_EQ(test.y, test.g); EXPECT_EQ(test.y, test.t);	
}

TEST(TVec3Test, AssignmentCheck)
{
	Vec2 test = Vec2(1, 2);

	EXPECT_EQ(test.x, 1); EXPECT_EQ(test.y, 2);
}