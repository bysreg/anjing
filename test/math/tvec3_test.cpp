#include "math/tvec3.hpp"
#include "core/types.hpp"
#include "math/vecops.hpp"

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

TEST(TVec3Test, EqualityCheck)
{
	Vec3 test1 = Vec3(3, 4, 5);
	Vec3 test2 = Vec3(3, 4, 5);
	Vec3 test3 = Vec3(4, 5, 6);

	EXPECT_EQ(true, test1 == test2);
	EXPECT_EQ(false, test1 == test3);
}

TEST(TVec3Test, AdditionCheck)
{
	Vec3 test = Vec3(4, 3, 2) + Vec3(1, 2, 3);

	EXPECT_EQ(true, test == Vec3(5, 5, 5));
}

TEST(TVec3Test, SubstractionCheck)
{
	Vec3 test = Vec3(4, 3, 2) - Vec3(1, 2, 3);

	EXPECT_EQ(true, test == Vec3(3, 1, -1));
}

TEST(TVec3Test, NegationCheck)
{
	Vec3 test(1, 2, 3);

	test = -test;

	EXPECT_EQ(test==Vec3(-1, -2, -3), true);
}

TEST(TVec3Test, DivideByScalarCheck)
{
	Vec3 test = (Vec3(6, 8, 10) / 2.0f);	
	EXPECT_EQ(true, test == Vec3(3, 4, 5));
}

TEST(TVec3Test, NormalizeCheck)
{
	Vec3 test1 = Normalize(Vec3(5, 0, 0));
	Vec3 test2 = Normalize(Vec3(0, 3, 0));
	Vec3 test3 = Normalize(Vec3(0, 0, 4));

	EXPECT_EQ(test1 == Vec3(1, 0, 0), true);
	EXPECT_EQ(test2 == Vec3(0, 1, 0), true);
	EXPECT_EQ(test3 == Vec3(0, 0, 1), true);
}

TEST(TVec3Test, DotCheck)
{
	Vec3 a(1, 3, 5);
	Vec3 b(4, 2, 5);
	float test = Dot(a, b);
	EXPECT_EQ(test, 35);
}

TEST(TVec3Test, CrossCheck)
{
	Vec3 a(1, 0, 0);
	Vec3 b(0, 1, 0);
	Vec3 test = Cross(a, b);
	EXPECT_EQ(true, test == Vec3(0, 0, 1));

	Vec3 a2(2, 0, 0);
	Vec3 b2(0, 2, 0);
	Vec3 test2 = Cross(a2, b2);
	EXPECT_EQ(true, test2 == Vec3(0, 0, 4));
}