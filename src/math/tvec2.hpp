#pragma once

namespace anjing
{
	namespace math
	{

		///
		/// \brief TVec2 is a template class (header-only) to store 2 element vector
		///
		template<typename T>
		struct TVec2
		{			

			union
			{
				T x, r, s;
			};

			union
			{
				T y, g, t;
			};
		
			///
			/// Default constructor for TVec2
			///			
			TVec2() : x(0), y(0)
			{}

			/// 
			/// Alternative constructor for TVec2
			///			
			TVec2(const T& a, const T& b) : x(a), y(b)
			{}								

			TVec2<T>& operator=(const TVec2<T>& v);

		};

		///////////////// implementation

		template<typename T>
		TVec2<T>& TVec2<T>::operator=(const TVec2<T>& v)
		{
			this->x = v.x;
			this->y = v.y;			
			return *this;
		}

		typedef TVec2<float> Vec2;
	}
}