#pragma once

#include "math/tvec4.hpp"
#include "math/vecops.hpp"

#include <cstddef>
#include <iostream>

namespace anjing
{
	namespace math
	{

		template<typename T>
		struct TQuat
		{

			typedef TQuat<T> Type;

		public:
			///
			/// Default constructor for TQuat. TQuat will default to identity quaternion
			///
			TQuat();			

			///
			/// \brief Make this quaternion as identity quaternion
			///
			void SetAsIdentity();

			T w, x, y, z;

		};

		template<typename T>
		inline TQuat<T>::TQuat() : w(1), x(0), y(0), z(0)
		{}

		template<typename T>
		inline void TQuat<T>::SetAsIdentity()
		{
			w = 1; x = 0; y = 0; z = 0;
		}

		template<typename T>
		std::ostream& operator<<(std::ostream& os, const TQuat<T>& q)
		{
			os << q.w << " < " << q.x << " " << q.y << " " << q.z << " > " << std::endl;
			return os;
		}

		typedef TQuat<float> Quatf;
	}
}