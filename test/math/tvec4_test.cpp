#include "math/tvec4.hpp"
#include "core/types.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;
using namespace anjing::math;

TEST(TVec4Test, ConstructionCheck)
{
	TVec4<float> test;
	TVec4<int32> test2;
	TVec4<double> test3(1, 2, 3, 4);

	EXPECT_EQ(test.x, 0); EXPECT_EQ(test.y, 0); EXPECT_EQ(test.z, 0); EXPECT_EQ(test.w, 0);
	EXPECT_EQ(test2.x, 0); EXPECT_EQ(test2.y, 0); EXPECT_EQ(test2.z, 0); EXPECT_EQ(test2.w, 0);
	EXPECT_EQ(test3.x, 1); EXPECT_EQ(test3.y, 2); EXPECT_EQ(test3.z, 3); EXPECT_EQ(test3.w, 4);
}

TEST(TVec3Test, xyzrgbstpCheck)
{
	Vec4 test(1, 2, 3, 4);

	EXPECT_EQ(test.x, test.r); EXPECT_EQ(test.x, test.s);
	EXPECT_EQ(test.y, test.g); EXPECT_EQ(test.y, test.t);
	EXPECT_EQ(test.z, test.b); EXPECT_EQ(test.z, test.p);
	EXPECT_EQ(test.w, test.a); EXPECT_EQ(test.w, test.q);
}

TEST(TVec3Test, AssignmentCheck)
{
	Vec4 test = Vec4(1, 2, 3, 4);

	EXPECT_EQ(test.x, 1); EXPECT_EQ(test.y, 2); EXPECT_EQ(test.z, 3); EXPECT_EQ(test.w, 4);
}