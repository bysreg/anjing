#pragma once

#include "math/tquat.hpp"
#include "math/tvec3.hpp"

#include <cmath>

namespace anjing
{
	namespace math
	{

		///
		/// \brief Perform conjugate operation on this quaternion
		///
		/// if q = <w, x, y, z>, its conjugate is defined as q' = <w, -x, -y, -z>
		///
		template<typename T>
		void Conjugate(TQuat<T>* a) 
		{ 
			a->x *= -1; a->y *= -1; a->z *= -1; 
		}

		/// \brief Return a conjugate quaternion of a
		template<typename T>
		TQuat<T> Conjugate(TQuat<T> const& a) 
		{
			return TQuat<T>(a.w, -a.x, -a.y, -a.z);
		}

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

		/// \brief Returns inverse of a quaternion
		template<typename T>
		TQuat<T> Inverse(TQuat<T> const& q)
		{
			return Conjugate(q) / SqrMagnitude(q);
		}

		/// \brief Create quaternion with specified angle (in rad) and axis of rotation
		template<typename T>
		TQuat<T> CreateFromAngleAxis(T angle, TVec3<T> const& axis)
		{
			T sin_val = std::sin(angle * 0.5f);
			return TQuat<T>(
				std::cos(angle * 0.5f),
				sin_val * axis.x,
				sin_val * axis.y,
				sin_val * axis.z
				);
		}

		/// \brief Get angle and axis from a quaternion. This will modify the parameters
		template<typename T>
		void GetAngleAxis(TQuat<T> const& q, T& angle, TVec3<T>& axis)
		{
			angle = std::acos(q.w) * 2;
			T sin_val = std::sin(angle * 0.5f);
			axis = TVec3<T>(q.x / sin_val, q.y / sin_val, q.z / sin_val);
		}

	}
}