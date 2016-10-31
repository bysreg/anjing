#include "math/tvec4.hpp"
#include "core/types.hpp"
#include "math/vecops.hpp"

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

TEST(TVec4Test, xyzrgbstpCheck)
{
	Vec4f test(1, 2, 3, 4);

	EXPECT_EQ(test.x, test.r); EXPECT_EQ(test.x, test.s);
	EXPECT_EQ(test.y, test.g); EXPECT_EQ(test.y, test.t);
	EXPECT_EQ(test.z, test.b); EXPECT_EQ(test.z, test.p);
	EXPECT_EQ(test.w, test.a); EXPECT_EQ(test.w, test.q);
}

TEST(TVec4Test, subscriptCheck)
{
	Vec4f test(1, 2, 3, 4);

	EXPECT_EQ(test.x, test[0]);
	EXPECT_EQ(test.y, test[1]);
	EXPECT_EQ(test.z, test[2]);
	EXPECT_EQ(test.w, test[3]);
}

TEST(TVec4Test, AssignmentCheck)
{
	Vec4f test = Vec4f(1, 2, 3, 4);

	EXPECT_EQ(test.x, 1); EXPECT_EQ(test.y, 2); EXPECT_EQ(test.z, 3); EXPECT_EQ(test.w, 4);
}

TEST(TVec4Test, EqualityCheck)
{
	Vec4f test1 = Vec4f(3, 4, 5, 6);
	Vec4f test2 = Vec4f(3, 4, 5, 6);
	Vec4f test3 = Vec4f(4, 5, 6, 7);

	EXPECT_TRUE(test1 == test2);
	EXPECT_FALSE(test1 == test3);
}

TEST(TVec4Test, AdditionCheck)
{
	Vec4f test = Vec4f(4, 3, 2, 1) + Vec4f(1, 2, 3, 4);

	EXPECT_EQ(true, test == Vec4f(5, 5, 5, 5));
}

TEST(TVec4Test, SubstractionCheck)
{
	Vec4f test = Vec4f(4, 3, 2, 1) - Vec4f(1, 2, 3, 4);

	EXPECT_EQ(true, test == Vec4f(3, 1, -1, -3));
}

TEST(TVec4Test, DivideByScalarCheck)
{
	Vec4f test = (Vec4f(6, 8, 10, 12) / 2.0f);
	EXPECT_EQ(true, test == Vec4f(3, 4, 5, 6));
}

TEST(TVec4Test, NormalizeCheck)
{
	Vec4f test1 = Normalize(Vec4f(5, 0, 0, 0));
	Vec4f test2 = Normalize(Vec4f(0, 3, 0, 0));
	Vec4f test3 = Normalize(Vec4f(0, 0, 4, 0));
	Vec4f test4 = Normalize(Vec4f(0, 0, 0, 2));

	EXPECT_EQ(test1 == Vec4f(1, 0, 0, 0), true);
	EXPECT_EQ(test2 == Vec4f(0, 1, 0, 0), true);
	EXPECT_EQ(test3 == Vec4f(0, 0, 1, 0), true);
	EXPECT_EQ(test4 == Vec4f(0, 0, 0, 1), true);
}

TEST(TVec4Test, DotCheck)
{
	Vec4f a(1, 3, 5, 6);
	Vec4f b(4, 2, 5, 2);
	float test = Dot(a, b);
	EXPECT_EQ(test, 47);
}