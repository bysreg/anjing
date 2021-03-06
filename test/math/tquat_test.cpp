#include "math/quatops.hpp"
#include "math/const.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

using namespace anjing::core;
using namespace anjing::math;

#define TEST_TITLE TQuatfTest

TEST(TEST_TITLE, Construction)
{
	Quatf q;

	EXPECT_EQ(1, q.w);
	EXPECT_EQ(0, q.x);
	EXPECT_EQ(0, q.y);
	EXPECT_EQ(0, q.z);

	Quatf q2(1, 2.2f, 3.3f, 4.4f);
	
	EXPECT_EQ(1, q2.w);
	EXPECT_EQ(2.2f, q2.x);
	EXPECT_EQ(3.3f, q2.y);
	EXPECT_EQ(4.4f, q2.z);

	Quatf q3 = q2;

	EXPECT_EQ(q3.w, q2.w);
	EXPECT_EQ(q3.x, q2.x);
	EXPECT_EQ(q3.y, q2.y);
	EXPECT_EQ(q3.z, q2.z);
}

TEST(TEST_TITLE, Identity)
{
	Quatf q;
	q.SetAsIdentity();

	EXPECT_EQ(1, q.w);
	EXPECT_EQ(0, q.x);
	EXPECT_EQ(0, q.y);
	EXPECT_EQ(0, q.z);
}

TEST(TEST_TITLE, Conjugate)
{
	Quatf q(1, 2.2f, 3.3f, 4.4f);
	Quatf q_c = Conjugate(q);
	EXPECT_EQ(1, q_c.w);
	EXPECT_EQ(-2.2f, q_c.x);
	EXPECT_EQ(-3.3f, q_c.y);
	EXPECT_EQ(-4.4f, q_c.z);
	
	Conjugate(&q);
	EXPECT_EQ(q_c.w, q.w);
	EXPECT_EQ(q_c.x, q.x);
	EXPECT_EQ(q_c.y, q.y);
	EXPECT_EQ(q_c.z, q.z);
}

TEST(TEST_TITLE, Equality)
{
	Quatf q(2, 3, 4, 5);
	Quatf copy = q;

	EXPECT_EQ(copy, q);
}

TEST(TEST_TITLE, Addition)
{
	Quatf a(1, 2, 3, 4);
	Quatf b(2, 3, 4, 5);
	Quatf c = a + b;

	EXPECT_EQ(3, c.w);
	EXPECT_EQ(5, c.x);
	EXPECT_EQ(7, c.y);
	EXPECT_EQ(9, c.z);
}

TEST(TEST_TITLE, Substraction)
{
	Quatf a(1, 2, 3, 4);
	Quatf b(2, 4, 6, 8);
	Quatf c = a - b;

	EXPECT_EQ(-1, c.w);
	EXPECT_EQ(-2, c.x);
	EXPECT_EQ(-3, c.y);
	EXPECT_EQ(-4, c.z);
}

TEST(TEST_TITLE, QuaternionMultiplication)
{
	Quatf a(1, 2, 3, 4);
	Quatf b(2, 4, 6, 8);
	Quatf c = a * b;

	EXPECT_EQ(-56, c.w);
	EXPECT_EQ(8, c.x);
	EXPECT_EQ(12, c.y);
	EXPECT_EQ(16, c.z);
}

TEST(TEST_TITLE, ScalarQuaternionMultiplication)
{
	Quatf a(1, 2, 3, 4);
	float scalar = 3;
	Quatf c = a * scalar;
	Quatf d = scalar * a;

	EXPECT_EQ(3, c.w);
	EXPECT_EQ(6, c.x);
	EXPECT_EQ(9, c.y);
	EXPECT_EQ(12, c.z);

	EXPECT_EQ(d.w, c.w);
	EXPECT_EQ(d.x, c.x);
	EXPECT_EQ(d.y, c.y);
	EXPECT_EQ(d.z, c.z);
}

TEST(TEST_TITLE, ScalarDivision)
{
	Quatf a(1, 2, 3, 4);
	float scalar = 2;
	Quatf val = a / scalar;

	EXPECT_EQ(0.5f, val.w);
	EXPECT_EQ(1, val.x);
	EXPECT_EQ(1.5f, val.y);
	EXPECT_EQ(2, val.z);
}

TEST(TEST_TITLE, Dot)
{
	Quatf a(1, 2, 3, 4);
	Quatf b(2, 3, 4, 5);

	float val = Dot(a, b);
	EXPECT_EQ(40, val);
}

TEST(TEST_TITLE, SqrMagnitude)
{
	Quatf a(1, 2, 3, 4);
	float val = SqrMagnitude(a);

	EXPECT_EQ(30, val);
	EXPECT_EQ(Dot(a, a), val);

	// a * a' == SqrMagnitude(a) == a' * a
	Quatf ca = Conjugate(a);
	auto d = ca * a;
	auto e = a * ca;
	EXPECT_EQ(d.w, val);
	EXPECT_EQ(d.x, 0);
	EXPECT_EQ(d.y, 0);
	EXPECT_EQ(d.z, 0);
	EXPECT_EQ(e.w, val);
	EXPECT_EQ(e.x, 0);
	EXPECT_EQ(e.y, 0);
	EXPECT_EQ(e.z, 0);
}

TEST(TEST_TITLE, Inverse)
{
	Quatf q(1, 2, 3, 4);
	Quatf inv_q = Inverse(q);
	Quatf result = q * inv_q;
	float result_sqrmag = SqrMagnitude(result);

	EXPECT_EQ(1, result.w);
	EXPECT_EQ(1, result_sqrmag);

	Quatf result2 = inv_q * q;
	float result2_sqrmag = SqrMagnitude(result2);
	EXPECT_EQ(1, result2.w);
	EXPECT_EQ(1, result2_sqrmag);
}

TEST(TEST_TITLE, CreateFromAngleAxis)
{
	float angle = anjing::math::PI / 2.0f; // 90 degree
	Vec3f axis(0, 1, 0);
	Quatf q = CreateFromAngleAxis(angle, axis);
	EXPECT_EQ(std::cos(angle * 0.5f), q.w);
	EXPECT_EQ(0, q.x);
	EXPECT_EQ(std::sin(angle * 0.5f), q.y);
	EXPECT_EQ(0, q.z);
}

TEST(TEST_TITLE, GetAngleAxis)
{
	float angle = anjing::math::PI / 2.0f; // 90 degree
	Vec3f axis(0, 1, 0);
	Quatf q = CreateFromAngleAxis(angle, axis);

	float check_angle;
	Vec3f check_axis;
	GetAngleAxis(q, check_angle, check_axis);
	EXPECT_EQ(check_angle, angle);
	EXPECT_EQ(check_axis, axis);
}

TEST(TEST_TITLE, Print)
{
	Quatf q;

	std::cout << q << std::endl;
}