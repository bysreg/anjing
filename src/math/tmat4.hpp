#pragma once

#include "math/tvec4.hpp"
#include "math/vecops.hpp"

#include <cstddef>
#include <iostream>
#include <initializer_list>

namespace anjing
{
	namespace math
	{

		template<typename T>
		struct TMat4
		{

			using Type = TVec4<T>;

		public:
			
			/// Default constructor for TMat4. Matrix will be filled with all zeros initially
			TMat4();

			/// alternative constuctor for TMat4
			TMat4(Type a, Type b, Type c, Type d);

			/// Make this matrix as identity matrix
			void SetAsIdentity();

			//operators
			typename TMat4<T>::Type& operator[](std::size_t i);
			typename TMat4<T>::Type const & operator[](std::size_t i) const;

			constexpr std::size_t Rows() const { return 4; }
			constexpr std::size_t Cols() const { return 4; }

		private:

			Type value[4];

		};

		template<typename T>
		TMat4<T>::TMat4()
		{}

		template<typename T>
		TMat4<T>::TMat4(Type a, Type b, Type c, Type d)
		{
			value[0] = a;
			value[1] = b;
			value[2] = c;
			value[3] = d;
		}

		template<typename T>
		void TMat4<T>::SetAsIdentity()
		{
			value[0] = Type(1, 0, 0, 0);
			value[1] = Type(0, 1, 0, 0);
			value[2] = Type(0, 0, 1, 0);
			value[3] = Type(0, 0, 0, 1);
		}

		template<typename T>
		typename TMat4<T>::Type & TMat4<T>::operator[](std::size_t i)
		{
			return value[i];
		}

		template<typename T>
		typename TMat4<T>::Type const & TMat4<T>::operator[](std::size_t i) const
		{
			return value[i];
		}

		template<typename T>
		bool operator==(const TMat4<T>& a, const TMat4<T>& b)
		{
			return (a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) && (a[3] == b[3]);
		}

		template<typename T>
		bool operator!=(const TMat4<T>& a, const TMat4<T>& b)
		{
			return (a[0] != b[0]) || (a[1] != b[1]) || (a[2] != b[2]) || (a[3] != b[3]);
		}

		template<typename T>
		TMat4<T> operator*(const TMat4<T>& a, const TMat4<T>& b)
		{
			TMat4<T> ret;
			constexpr const size_t rows = a.Rows();
			constexpr const size_t cols = a.Cols();

			// TODO: replace with faster algorithm
			for (size_t i = 0; i < rows; ++i)
			{
				for (size_t j = 0; j < cols; ++j)
				{
					for (size_t k = 0; k < cols; ++k)
					{
						ret[i][j] += a[i][k] * b[k][j];
					}
				}
			}

			return ret;
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

		using Mat4f = TMat4<float>;
	}
}