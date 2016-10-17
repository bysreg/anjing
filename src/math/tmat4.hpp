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
		struct TMat4
		{

			using Type = TVec4<T>;

		public:
			///
			/// Default constructor for TMat4
			///
			TMat4();			

			///
			/// \brief Make this matrix as identity matrix
			///
			void SetAsIdentity();

			//operators
			typename TMat4<T>::Type& operator[](std::size_t i);
			typename TMat4<T>::Type const & operator[](std::size_t i) const;

		private:

			Type value[4];

		};

		template<typename T>
		TMat4<T>::TMat4()
		{}

		template<typename T>
		inline void TMat4<T>::SetAsIdentity()
		{
			value[0] = Type(1, 0, 0, 0);
			value[1] = Type(0, 1, 0, 0);
			value[2] = Type(0, 0, 1, 0);
			value[3] = Type(0, 0, 0, 1);
		}

		template<typename T>
		inline typename TMat4<T>::Type & TMat4<T>::operator[](std::size_t i)
		{
			return value[i];
		}

		template<typename T>
		inline typename TMat4<T>::Type const & TMat4<T>::operator[](std::size_t i) const
		{
			return value[i];
		}

		template<typename T>
		std::ostream& operator<<(std::ostream& os, const TMat4<T>& mat)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					os << (mat[i][j]) << "\t";					
				}
				os << std::endl;
			}

			return os;
		}

		using Mat4 = TMat4<float>;
	}
}