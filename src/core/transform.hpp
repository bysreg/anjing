#pragma once

#include "core/component.hpp"
#include "math/tvec3.hpp"
#include "math/tmat4.hpp"

namespace anjing
{
	namespace core
	{
		class Transform : public Component
		{

		public:
			
			/// \brief Default constructor for Transform
			Transform();

			/// \brief Returns current world position
			anjing::math::Vec3f GetWorldPosition() const { return wpos; }

			/// \brief Returns current transform matrix
			anjing::math::Mat4f GetMat() const { return mat; }

		private:
			
			anjing::math::Vec3f wpos;
			anjing::math::Mat4f mat;

			virtual void OnAdded() override;

		};
	}
}