#pragma once

#include "math/tmat4.hpp"
#include "math/tvec3.hpp"
#include "math/vecops.hpp"

#include <cmath>

namespace anjing
{
	namespace math
	{

		///
		/// \brief Creates a viewing matrix
		///
		template<typename T>
		inline TMat4<T> LookAt(TVec3<T> const & eye, TVec3<T> const & center, TVec3<T> const & up)
		{
			TVec3<T> w = Normalize(center - eye);
			TVec3<T> u = Normalize(Cross(w, up));
			TVec3<T> v = Cross(u, w); // don't need to normalize this, bcos cross product of base unit vector is another base unit vector

			TMat4<T> ret;
			ret.SetAsIdentity();

			ret[0][0] = u.x;
			ret[1][0] = u.y;
			ret[2][0] = u.z;
			ret[3][0] = -Dot(eye, u);
			ret[0][1] = v.x;
			ret[1][1] = v.y;
			ret[2][1] = v.z;
			ret[3][1] = -Dot(eye, v);
			ret[0][2] = -w.x;
			ret[1][2] = -w.y;
			ret[2][2] = -w.z;
			ret[3][2] = Dot(eye, w);

			return ret;
		}

		///
		/// \brief Creates a perspective matix
		///
		/// \a fovy is degree of field of view in the y axis
		/// \a aspect is ratio between width and height of the screen
		/// \a near is z distance of the nearest object that will get drawn into the camera
		/// \a far is the farthest z distance of the object that will get drawn into the camera
		///
		template<typename T>
		inline TMat4<T> perspective(T fovy, T aspect, T near, T far)
		{
			T const ynear = std::tan(fovy / static_cast<T>(2));

			TMat4<T> ret;
			T one = static_cast<T>(1);
			T two = static_cast<T>(2);
			ret[0][0] = one / (aspect * ynear); // width
			ret[1][1] = one / ynear; // height
			ret[2][2] = -(far + near) / (far - near);
			ret[2][3] = -one;
			ret[3][2] = -(two * far * near) / (far - near);
			return ret;
		}

	}
}
