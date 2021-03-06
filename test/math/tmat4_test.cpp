#include "math/tmat4.hpp"
#include "core/types.hpp"
#include "math/vecops.hpp"
#include "math/matops.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace anjing::core;
using namespace anjing::math;

#define TEST_TITLE TMat4Test

TEST(TEST_TITLE, ConstructionCheck)
{
	Mat4f mat;

	// check all elements of the matrix are zero initially
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			EXPECT_EQ(mat[i][j], 0);
		}
	}

	Mat4f mat2 = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
	int count = 0;
	for (size_t i = 0; i < mat2.Rows(); ++i)
	{
		for (size_t j = 0; j < mat2.Cols(); ++j)
		{
			EXPECT_EQ(++count, mat2[i][j]);
		}
	}
}

TEST(TEST_TITLE, IdentityCheck)
{
	Mat4f mat;
	mat.SetAsIdentity();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				EXPECT_EQ(mat[i][j], 1);
			else
				EXPECT_EQ(mat[i][j], 0);
		}
	}
}

TEST(TEST_TITLE, EqualityCheck)
{
	Mat4f a;
	Mat4f b;
	float count = 0;
	for (size_t i = 0; i < a.Rows(); ++i)
	{
		for (size_t j = 0; j < a.Cols(); ++j)
		{
			a[i][j] = ++count;
			b[i][j] = a[i][j];
		}
	}

	EXPECT_TRUE(a == b);

	// for each element, we try to change b's current element to something else
	for (size_t i = 0; i < a.Rows(); ++i)
	{
		for (size_t j = 0; j < a.Cols(); ++j)
		{
			b[i][j] = a[i][j] + 100;
			EXPECT_FALSE(a == b);
			b[i][j] = a[i][j];
		}
	}

	EXPECT_TRUE(a == b);
}

TEST(TEST_TITLE, InequalityCheck)
{
	Mat4f a;
	Mat4f b;
	float count = 0;
	for (size_t i = 0; i < a.Rows(); ++i)
	{
		for (size_t j = 0; j < a.Cols(); ++j)
		{
			a[i][j] = ++count;
			b[i][j] = a[i][j];
		}
	}

	EXPECT_FALSE(a != b);

	// for each element, we try to change b's current element to something else
	for (size_t i = 0; i < a.Rows(); ++i)
	{
		for (size_t j = 0; j < a.Cols(); ++j)
		{
			b[i][j] = a[i][j] + 100;
			EXPECT_TRUE(a != b);
			b[i][j] = a[i][j];
		}
	}

	EXPECT_FALSE(a != b);
}

TEST(TEST_TITLE, PrintCheck)
{
	Mat4f mat;

	std::cout << mat << std::endl;
}

TEST(TEST_TITLE, LookAtCheck)
{
	Vec3f eye(0, 0, 0);
	Vec3f center(0, 0, 1);
	Vec3f up(0, 1, 0);

	Mat4f view = LookAt(eye, center, up);
	std::cout << view << std::endl;
	
	// FIXME: not sure what the value exactly supposed to be
}

TEST(TEST_TITLE, MultiplicationCheck)
{
	Mat4f a = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 16 } };
	Mat4f b = { { 1, 5, 9, 13 },{ 2, 6, 10, 14 },{ 3, 7, 11, 15 },{ 4, 8, 12, 16 } };
	Mat4f i; // identity
	i.SetAsIdentity();
	
	// check for identity rule
	EXPECT_TRUE(b * i == b);
	EXPECT_TRUE(i * b == b);
	EXPECT_TRUE(a * i == a);
	EXPECT_TRUE(i * a == a);
	EXPECT_TRUE(i * i == i);

	Mat4f result = { {30, 70, 110, 150}, {70, 174, 278, 382}, {110, 278, 446, 614}, {150, 382, 614, 846} };
	EXPECT_TRUE((a * b) == result);
}