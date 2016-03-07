#pragma once

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
			TVec4(const T& a, const T& b, const T& c, const T& d) : x(a), y(b), z(c), w(d)
			{}								

			TVec4<T>& operator=(const TVec4<T>& v);

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
		bool operator== (const TVec4<T>& a, TVec4<T> b)
		{
			return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w);
		}

		typedef TVec4<float> Vec4;
	}
}