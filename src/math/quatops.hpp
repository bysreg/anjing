#pragma once

#include "math/tquat.hpp"

namespace anjing
{
	namespace math
	{

		/// \brief Returns a dot product of two quaternions
		template<typename T>
		T Dot(TQuat<T> const& a, TQuat<T> const& b)
		{
			return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
		}

		/// \brief Returns Square magnitude of a quaternion
		///
		/// Propertiy of quaternion's square magnitude is it is the same as
		/// SqrMagnitude(q) == Dot(q, q) == (q * q.conjugate()).w == (q.conjugate() * q).w
		template<typename T>
		T SqrMagnitude(TQuat<T> const& q)
		{
			return Dot(q, q);
		}

	}
}