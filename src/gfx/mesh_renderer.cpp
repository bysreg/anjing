#include "mesh_renderer.hpp"
#include "material.hpp"
#include "shader.hpp"
#include "mesh.hpp"

#include <GL/glew.h>

#define ANJING_BUFFER_OFFSET(offset) (static_cast<char*>(nullptr) + (offset))

using namespace anjing::gfx;

void MeshRenderer::Render()
{
	Shader* shader = material->GetShader();

	shader->SetActive();

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertices_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indices_id);

	glEnableVertexAttribArray(shader->GetLocalPositionId());
	//glVertexAttribPointer(shader->GetLocalPositionId(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), );

}

void anjing::gfx::MeshRenderer::SetMesh(Mesh const * const mesh)
{
	this->mesh = mesh;
}

void anjing::gfx::MeshRenderer::SetMaterial(Material const * const material)
{
	this->material = material;
}
