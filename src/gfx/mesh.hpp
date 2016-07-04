#pragma once

#include "core/component.hpp"
#include "gfx/vertex.hpp"

#include <vector>
#include <cstddef>
#include <GL/glew.h>

// forward declarations
namespace anjing
{
	namespace gfx 
	{
		class MeshRenderer;
	}
}

namespace anjing
{
	namespace gfx 
	{

		class Mesh
		{

			friend class anjing::gfx::MeshRenderer;

		public:

			///
			/// \brief Returns vertex list count
			///
			size_t GetVertexCount() const;

			///
			/// \brief Returns index list count
			///
			size_t GetIndexCount() const;			

			///
			/// \brief Adds \a vertex to the vertices
			///
			void AddVertex(Vertex vertex);

			///
			/// \brief Adds \a index to the indices
			///
			void AddIndex(anjing::core::uint32 index);

			///
			/// \brief Call this after modifying the mesh, to update the mesh
			///
			/// If you didn't call this after modifying the mesh, the mesh will
			/// display the old mesh instead
			///
			void UpdateMesh();

			///
			/// \brief Default constructor for Mesh
			///
			Mesh();		

			///
			/// \brief Return whether Mesh has been modified but not yet updated
			///
			bool IsDirty() inline const
			{
				return is_dirty;
			}

		private:
			
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;

			GLuint vertices_id = 0;
			GLuint indices_id = 0;
			bool is_dirty = true;
			
		};

	}
}