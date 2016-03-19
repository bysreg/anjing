#pragma once

#include "core/component.hpp"
#include "math/tvec3.hpp"

namespace anjing
{
	namespace core
	{
		class Transform : public Component
		{

		public:
			
			///
			/// \brief Returns current world position
			///
			inline anjing::math::Vec3 GetWorldPosition() const
			{
				return wpos;
			}			

		private:
			
			anjing::math::Vec3 wpos;					

			virtual void OnAdded() override;

		};
	}
}