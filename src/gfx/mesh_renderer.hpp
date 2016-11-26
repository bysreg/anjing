#pragma once

#include "core/component.hpp"

namespace anjing
{
	namespace gfx
	{
		//forward declarations
		class Mesh;
		class Material;

		class MeshRenderer : public anjing::core::Component
		{
			friend class anjing::core::GameObject;

		public:
			///
			/// \brief This function will render the GameObject its attached to to the screen
			///
			void Render();

			///
			/// \brief Assign mesh to be rendered
			///
			void SetMesh(Mesh const * const new_mesh) { mesh = new_mesh; }

			///
			/// \brief Assign material to be renderer
			///
			void SetMaterial(Material const * const new_material) { material = new_material; }

		protected:
			///
			/// \brief Default constructor for MeshRenderer
			///
			MeshRenderer() : mesh(nullptr) {}
		
			virtual ~MeshRenderer() {}

		private:

			Mesh const * mesh;
			Material const * material;
		};
	}
}