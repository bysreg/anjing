#include "mesh_renderer.hpp"

#include "material.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "core/assert.hpp"
#include "core/game_object.hpp"
#include "core/scene.hpp"

#include <GL/glew.h>

#define ANJING_BUFFER_OFFSET(offset) (static_cast<char*>(nullptr) + (offset))

namespace anjing
{
namespace gfx
{
	MeshRenderer::MeshRenderer()
		: mesh(nullptr), material(nullptr)
	{}

	MeshRenderer::~MeshRenderer() 
	{
		Adelete(mesh);
		Adelete(material);
	}

	void MeshRenderer::SetMesh(Mesh* new_mesh)
	{
		mesh = new_mesh;
	}

	void MeshRenderer::SetMaterial(Material* new_material) 
	{ 
		material = new_material;
	}

	void MeshRenderer::Render()
	{
		Shader* shader = material->GetShader();
		//anjing::gfx::Camera* cam = anjing::core::Scene::GetInstance().GetCamera();

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		shader->SetActive();

		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertices_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indices_id);

		// set shader attributes
		glEnableVertexAttribArray(shader->GetLocalPositionId());
		glVertexAttribPointer(shader->GetLocalPositionId(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
		glEnableVertexAttribArray(shader->GetColorId());
		glVertexAttribPointer(shader->GetColorId(), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
		/*glEnableVertexAttribArray(shader->GetUvId());
		glVertexAttribPointer(shader->GetUvId(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tex_coord)));
		glEnableVertexAttribArray(shader->GetLocalNormalId());
		glVertexAttribPointer(shader->GetLocalNormalId(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));*/

		// set shader uniforms
		/*GLint uni_world = glGetUniformLocation(shader->GetGLProgram(), "u_world");
		ANJING_ASSERT(uni_world != -1);
		anjing::math::Mat4f world = GetOwner()->GetTransform()->GetMat();
		glUniformMatrix4fv(uni_world, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&world));
		
		GLint uni_proj_view = glGetUniformLocation(shader->GetGLProgram(), "u_proj_view");
		ANJING_ASSERT(uni_proj_view != -1);
		anjing::math::Mat4f proj_view = cam->GetProjMat() * cam->GetViewMat();
		glUniformMatrix4fv(uni_proj_view, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&proj_view));
		*/
		glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, 0);

		//unbind all previous binding
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
}

