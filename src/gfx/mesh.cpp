#include "mesh.hpp"

using namespace anjing::gfx;
using namespace anjing::core;

size_t anjing::gfx::Mesh::GetVertexCount() const
{
	return vertices.size();
}

size_t anjing::gfx::Mesh::GetIndexCount() const
{
	return indices.size();
}

void anjing::gfx::Mesh::AddVertex(Vertex vertex)
{
	vertices.push_back(vertex);
}

void anjing::gfx::Mesh::AddIndex(uint32 index)
{
	indices.push_back(index);
}

Mesh::Mesh()
{
	vertices.reserve(3);
	indices.reserve(3);
}
