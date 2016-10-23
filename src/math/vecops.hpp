#pragma once

#include "math/tvec2.hpp"
#include "math/tvec3.hpp"
#include "math/tvec4.hpp"

#include <cmath>

namespace anjing
{
	namespace math
	{

		template<typename T>
		T Dot(TVec2<T> const & a, TVec2<T> const & b)
		{
			return (a.x * b.x) + (a.y * b.y);
		}

		template<typename T>
		T Dot(TVec3<T> const & a, TVec3<T> const & b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}

		template<typename T>
		T Dot(TVec4<T> const & a, TVec4<T> const & b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		}
		
		template<typename T>
		TVec3<T> Cross(TVec3<T> const & a, TVec3<T> const & b)
		{
			return TVec3<T>(
				a.y*b.z - a.z*b.y,
				a.z*b.x - a.x*b.z,
				a.x*b.y - a.y*b.x
				);
		}

		template<typename T, template<typename> class VecType >
		VecType<double> Normalize(VecType<double> const & x)
		{
			return x / (sqrt(Dot(x, x)));
		}

		template<template<typename> class VecType >
		VecType<float> Normalize(VecType<float> const & x)
		{
			return x / (sqrtf(Dot(x, x)));
		}
	}
}