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
	is_dirty = true;
}

void anjing::gfx::Mesh::AddIndex(uint32 index)
{
	indices.push_back(index);
	is_dirty = true;
}

void anjing::gfx::Mesh::UpdateMesh()
{
	// delete first in case we already generate buffer on that id
	if (vertices_id != 0)
	{
		glDeleteBuffers(1, &vertices_id);
		glDeleteBuffers(1, &indices_id);
	}

	printf("1");
	glGenBuffers(1, &vertices_id);
	
	printf("2");
	glBindBuffer(GL_ARRAY_BUFFER, vertices_id);

	printf("3");
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	printf("4");
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indices_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	is_dirty = false;
}

Mesh::Mesh()
{
	vertices.reserve(3);
	indices.reserve(3);
}
