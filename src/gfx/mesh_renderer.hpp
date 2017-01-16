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

			// overrides from component
			// component's destructor must be public. See Component's destructor function
			~MeshRenderer() override;

			///
			/// \brief This function will render the GameObject its attached to to the screen
			///
			void Render();

			///
			/// \brief Assign mesh to be rendered. This renderer now owns the pointer
			///
			void SetMesh(Mesh* new_mesh);

			///
			/// \brief Assign material to be renderer
			///
			void SetMaterial(Material* new_material);


		protected:
			///
			/// \brief Default constructor for MeshRenderer
			///
			MeshRenderer();

		private:

			// mesh renderer owns these pointers
			class Mesh* mesh;
			class Material* material;
		};
	}
}