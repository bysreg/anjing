#include "math/tvec2.hpp"
#include "core/types.hpp"
#include "math/vecops.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;
using namespace anjing::math;

TEST(TVec2Test, ConstructionCheck)
{
	TVec2<float> test;
	TVec2<int32> test2;
	TVec2<double> test3(1, 2);

	EXPECT_EQ(test.x, 0); EXPECT_EQ(test.y, 0);
	EXPECT_EQ(test2.x, 0); EXPECT_EQ(test2.y, 0);
	EXPECT_EQ(test3.x, 1); EXPECT_EQ(test3.y, 2);
}

TEST(TVec2Test, xyzrgbstpCheck)
{
	Vec2f test(1, 2);

	EXPECT_EQ(test.x, test.r); EXPECT_EQ(test.x, test.s);
	EXPECT_EQ(test.y, test.g); EXPECT_EQ(test.y, test.t);	
}

TEST(TVec2Test, AssignmentCheck)
{
	Vec2f test = Vec2f(1, 2);

	EXPECT_EQ(test.x, 1); EXPECT_EQ(test.y, 2);
}

TEST(TVec2Test, EqualityCheck)
{
	Vec2f test1 = Vec2f(3, 4);
	Vec2f test2 = Vec2f(3, 4);
	Vec2f test3 = Vec2f(4, 5);

	EXPECT_TRUE(test1 == test2);
	EXPECT_FALSE(test1 == test3);
}

TEST(TVec2Test, AdditionCheck)
{
	Vec2f test = Vec2f(4, 3) + Vec2f(1, 2);

	EXPECT_EQ(true, test == Vec2f(5, 5));
}

TEST(TVec2Test, SubstractionCheck)
{
	Vec2f test = Vec2f(4, 3) - Vec2f(1, 2);

	EXPECT_EQ(true, test == Vec2f(3, 1));
}

TEST(TVec2Test, DivideByScalarCheck)
{
	Vec2f test = (Vec2f(6, 8) / 2.0f);
	
	EXPECT_EQ(true, test == Vec2f(3, 4));
}

TEST(TVec2Test, NormalizeCheck)
{
	Vec2f test1 = Normalize(Vec2f(5, 0));
	Vec2f test2 = Normalize(Vec2f(0, 3));
	
	EXPECT_EQ(test1 == Vec2f(1, 0), true);
	EXPECT_EQ(test2 == Vec2f(0, 1), true);
}

TEST(TVec2Test, DotCheck)
{
	Vec2f a(1, 3);
	Vec2f b(4, 2);
	float test = Dot(a, b);
	EXPECT_EQ(test, 10);
}
