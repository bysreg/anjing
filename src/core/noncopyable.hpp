#pragma once

namespace anjing
{
	namespace core
	{

		///
		/// \brief A class with Noncopyable as base class in its base class hierarchy will make it noncopyable
		///
		/// Always inherit this class with private inheritance 
		///
		class Noncopyable
		{
		protected:

			Noncopyable() = default;
			~Noncopyable() = default;

		private:

			Noncopyable(const Noncopyable&) = delete;
			Noncopyable& operator=(const Noncopyable&) = delete;

		};
	}
}