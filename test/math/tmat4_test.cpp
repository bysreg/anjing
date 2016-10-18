#include "math/tmat4.hpp"
#include "core/types.hpp"
#include "math/vecops.hpp"
#include "math/matops.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace anjing::core;
using namespace anjing::math;

TEST(TMat4Test, ConstructionCheck)
{
	Mat4f mat;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			EXPECT_EQ(mat[i][j], 0);
		}
	}
}

TEST(TMat4Test, IdentityCheck)
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

TEST(TMat4Test, PrintCheck)
{
	Mat4f mat;

	std::cout << mat << std::endl;
}

TEST(TMat4Test, LookAtCheck)
{
	Vec3f eye(0, 0, 0);
	Vec3f center(0, 0, 1);
	Vec3f up(0, 1, 0);

	Mat4f view = LookAt(eye, center, up);
	std::cout << view << std::endl;
	
	// FIXME: not sure what the value exactly supposed to be
}