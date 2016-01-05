#pragma once

#include "core/component.hpp"
#include "gfx/vertex.hpp"

#include <vector>

namespace anjing
{
	namespace gfx 
	{

		class Mesh
		{
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
			/// \brief Default constructor for Mesh
			///
			Mesh();

		private:
			
			std::vector<Vertex> vertices;
			std::vector<anjing::core::uint32> indices;

		};

	}
}