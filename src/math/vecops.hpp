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
		inline T Dot(TVec2<T> const & a, TVec2<T> const & b)
		{
			return (a.x * b.x) + (a.y * b.y);
		}

		template<typename T>
		inline T Dot(TVec3<T> const & a, TVec3<T> const & b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}

		template<typename T>
		inline T Dot(TVec4<T> const & a, TVec4<T> const & b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		}

		template<typename T, template<typename> class VecType >
		inline VecType<double> Normalize(VecType<double> const & x)
		{
			return x / (sqrt(Dot(x, x)));
		}

		template<template<typename> class VecType >
		inline VecType<float> Normalize(VecType<float> const & x)
		{
			return x / (sqrtf(Dot(x, x)));
		}
	}
}