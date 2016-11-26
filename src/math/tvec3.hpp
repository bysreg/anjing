#pragma once

#include <cstddef>

namespace anjing
{
	namespace math
	{

		///
		/// \brief TVec3 is a template class (header-only) to store 3 element vector
		///
		template<typename T>
		struct TVec3
		{			

			union
			{
				T x, r, s;
			};

			union
			{
				T y, g, t;
			};

			union
			{
				T z, b, p;
			};

			///
			/// Default constructor for TVec3
			///			
			TVec3() : x(0), y(0), z(0)
			{}

			/// 
			/// Alternative constructor for TVec3
			///			
			TVec3(const T& i, const T& j, const T& k) : x(i), y(j), z(k)
			{}								

			inline std::size_t Size() const { return 3; }

			// operators
			TVec3<T>& operator=(const TVec3<T>& v);	
			TVec3<T> operator-();

		};

		///////////////// implementation

		template<typename T>
		TVec3<T>& TVec3<T>::operator=(const TVec3<T>& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return *this;
		}

		template<typename T>
		TVec3<T> operator+(const TVec3<T>& v1, const TVec3<T>& v2)
		{
			return TVec3<T>(
				v1.x + v2.x,
				v1.y + v2.y,
				v1.z + v2.z
				);
		}

		template<typename T>
		TVec3<T> operator-(const TVec3<T>& v1, const TVec3<T>& v2)
		{
			return TVec3<T>(
				v1.x - v2.x,
				v1.y - v2.y,
				v1.z - v2.z
				);
		}

		// unary -
		template<typename T>
		TVec3<T> TVec3<T>::operator-()
		{
			return TVec3<T>(
				-x,
				-y,
				-z
				);
		}

		template<typename T>
		TVec3<T> operator/(const TVec3<T>& v, T scalar)
		{
			return TVec3<T>(
				v.x / scalar,
				v.y / scalar, 
				v.z / scalar
				);
		}

		template<typename T>
		bool operator== (const TVec3<T>& v1, TVec3<T> v2)
		{
			return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
		}

		using Vec3f = TVec3<float>;
	}
}