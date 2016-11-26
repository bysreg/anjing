#include "mesh_renderer.hpp"
#include "material.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "core/assert.hpp"
#include "core/game_object.hpp"

#include <GL/glew.h>

#define ANJING_BUFFER_OFFSET(offset) (static_cast<char*>(nullptr) + (offset))

namespace anjing
{
namespace gfx
{
	void MeshRenderer::Render()
	{
		Shader* shader = material->GetShader();

		shader->SetActive();

		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertices_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indices_id);

		// set shader attributes
		glEnableVertexAttribArray(shader->GetLocalPositionId());
		glVertexAttribPointer(shader->GetLocalPositionId(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
		glEnableVertexAttribArray(shader->GetColorId());
		glVertexAttribPointer(shader->GetColorId(), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
		glEnableVertexAttribArray(shader->GetUvId());
		glVertexAttribPointer(shader->GetUvId(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tex_coord)));
		glEnableVertexAttribArray(shader->GetLocalNormalId());
		glVertexAttribPointer(shader->GetLocalNormalId(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

		// set shader uniforms
		//GLint uni_world = glGetUniformLocation(shader->GetGLProgram(), "u_world");
		//ANJING_ASSERT(uni_world != -1);
		//glUniformMatrix4fv(uni_world, 1, GL_FALSE, GetOwner()->GetTransform()->);
	}
}
}

