#pragma once

#include "core/component.hpp"

namespace anjing
{
	namespace gfx
	{
		class MeshRenderer : public anjing::core::Component
		{
			friend class anjing::core::GameObject;

		protected:
			///
			/// \brief Default constructor for MeshRenderer
			///
			MeshRenderer() {}

		public:
			///
			/// \brief This function will render the GameObject its attached to to the screen
			///
			void Render();
		};
	}
}