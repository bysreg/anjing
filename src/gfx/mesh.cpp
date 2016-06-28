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

void anjing::gfx::Mesh::UpdateMesh()
{
	glGenBuffers(1, &vertices_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_id);
	glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::Mesh()
{
	vertices.reserve(3);
	indices.reserve(3);
}
