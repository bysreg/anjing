#pragma once

#include <cstddef>

namespace anjing
{
	namespace math
	{

		///
		/// \brief TVec4 is a template class (header-only) to store 4 element vector
		///
		template<typename T>
		struct TVec4
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

			union
			{
				T w, a, q;
			};

			///
			/// Default constructor for TVec4
			///			
			TVec4() : x(0), y(0), z(0), w(0)
			{}

			/// 
			/// Alternative constructor for TVec4
			///			
			TVec4(const T& new_x, const T& new_y, const T& new_z, const T& new_w) : x(new_x), y(new_y), z(new_z), w(new_w)
			{}

			inline std::size_t Size() const { return 4; }

			// operators
			TVec4<T>& operator=(const TVec4<T>& v);
			T& operator[](std::size_t i);
			T const & operator[](std::size_t i) const;
		};

		///////////////// implementation

		template<typename T>
		TVec4<T>& TVec4<T>::operator=(const TVec4<T>& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->a = v.a;
			return *this;
		}

		template<typename T>
		inline T & TVec4<T>::operator[](std::size_t i)
		{			
			return (&x)[i];
		}

		template<typename T>
		inline T const & TVec4<T>::operator[](std::size_t i) const
		{
			return (&x)[i];
		}

		template<typename T>
		TVec4<T> operator+(const TVec4<T>& v1, const TVec4<T>& v2)
		{
			return TVec4<T>(
				v1.x + v2.x,
				v1.y + v2.y,
				v1.z + v2.z,
				v1.w + v2.w
				);
		}

		template<typename T>
		TVec4<T> operator-(const TVec4<T>& v1, const TVec4<T>& v2)
		{
			return TVec4<T>(
				v1.x - v2.x,
				v1.y - v2.y,
				v1.z - v2.z,
				v1.w - v2.w
				);
		}

		template<typename T>
		TVec4<T> operator/(const TVec4<T>& v, T scalar)
		{
			return TVec4<T>(
				v.x / scalar,
				v.y / scalar,
				v.z / scalar,
				v.w / scalar
				);
		}

		template<typename T>
		bool operator==(const TVec4<T>& v1, const TVec4<T>& v2)
		{
			return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
		}

		template<typename T>
		bool operator!=(const TVec4<T>& v1, const TVec4<T>& v2)
		{
			return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z) || (v1.w != v2.w);
		}

		using Vec4f = TVec4 <float>;
	}
}