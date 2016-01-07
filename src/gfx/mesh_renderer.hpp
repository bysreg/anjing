#pragma once

#include "core/component.hpp"

namespace anjing
{
	namespace gfx
	{
		//forward declarations
		class Mesh;

		class MeshRenderer : public anjing::core::Component
		{
			friend class anjing::core::GameObject;

		protected:
			///
			/// \brief Default constructor for MeshRenderer
			///
			MeshRenderer() : mesh(nullptr) {}

		public:
			///
			/// \brief This function will render the GameObject its attached to to the screen
			///
			void Render();

			///
			/// \brief Assign mesh to be rendered
			///
			void SetMesh(Mesh const * const mesh);

		private:

			Mesh const * mesh;

		};
	}
}