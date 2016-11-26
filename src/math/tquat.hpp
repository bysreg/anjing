#pragma once

#include "core/assert.hpp"

#include <iostream>

namespace anjing
{
	namespace math
	{

		template<typename T>
		struct TQuat
		{

			using Type = TQuat<T>;

		public:

			/// \brief Default constructor for TQuat. TQuat will default to identity quaternion
			TQuat();			

			/// \brief TQuat's constructor. w is the scalar component of the quaternion, the rest are the vector component
			explicit TQuat(T w, T x, T y, T z);

			/// \brief Make this quaternion as identity quaternion
			void SetAsIdentity();

			T w, x, y, z;

		};

		template<typename T>
		TQuat<T>::TQuat() : w(1), x(0), y(0), z(0)
		{}

		template<typename T>
		TQuat<T>::TQuat(T new_w, T new_x, T new_y, T new_z)
			: w(w), x(x), y(y), z(z)
		{}

		template<typename T>
		void TQuat<T>::SetAsIdentity()
		{
			w = 1; x = 0; y = 0; z = 0;
		}

		template<typename T>
		std::ostream& operator<<(std::ostream& os, const TQuat<T>& q)
		{
			os << q.w << " < " << q.x << " " << q.y << " " << q.z << " > " << std::endl;
			return os;
		}

		template<typename T>
		bool operator==(TQuat<T> const& a, TQuat<T> const& b)
		{
			return (a.w == b.w) && (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
		}

		template<typename T>
		TQuat<T> operator+(const TQuat<T>& a, const TQuat<T>& b)
		{
			return TQuat<T>(a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z);
		}

		template<typename T>
		TQuat<T> operator-(const TQuat<T>& a, const TQuat<T>& b)
		{
			return TQuat<T>(a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z);
		}

		template<typename T>
		TQuat<T> operator*(const TQuat<T>& a, const TQuat<T>& b)
		{
			const auto& sa = a.w; const auto& xa = a.x; const auto& ya = a.y; const auto& za = a.z;
			const auto& sb = b.w; const auto& xb = b.x; const auto& yb = b.y; const auto& zb = b.z;
			return TQuat<T>(sa*sb - xa*xb - ya*yb - za*zb,
							sa*xb + sb*xa + ya*zb - yb*za, 
							sa*yb + sb*ya + za*xb - zb*xa, 
							sa*zb + sb*za + xa*yb - xb*ya );
		}

		template<typename T>
		TQuat<T> operator*(const TQuat<T>& a, const T& scalar)
		{
			return TQuat<T>(scalar * a.w, scalar * a.x, scalar * a.y, scalar * a.z);
		}

		template<typename T>
		TQuat<T> operator*(const T& scalar, const TQuat<T>& a)
		{
			return a * scalar;
		}

		template<typename T>
		TQuat<T> operator/(TQuat<T> const& a, T const& scalar)
		{
			ANJING_ASSERT(scalar != 0);
			return TQuat<T>(a.w / scalar, a.x / scalar, a.y / scalar, a.z / scalar);
		}

		using Quatf = TQuat<float>;
	}
}