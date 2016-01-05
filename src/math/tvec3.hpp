#pragma once

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
			TVec3(const T& a, const T& b, const T& c) : x(a), y(b), z(c)
			{}								

			TVec3<T>& operator=(const TVec3<T>& v);

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

		typedef TVec3<float> Vec3;
	}
}