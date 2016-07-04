#include "camera.hpp"
#include "core/scene.hpp"
#include "math/matops.hpp"
#include "core/transform.hpp"
#include "core/game_object.hpp"

#include <GL/glew.h>

anjing::gfx::Camera::Camera() : fovy(3.14f / 4),
								aspect_ratio(1),
								near_clip(0.1f),
								far_clip(100)
{}

void anjing::gfx::Camera::Init()
{	
	UpdateProj();
	UpdateView();

	glViewport(0, 0, anjing::core::Scene::GetInstance().width, anjing::core::Scene::GetInstance().height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	/*initialize_static_models(scene.get_static_models(), scene.num_static_models());
	
	initialize_primitives();*/
}

void anjing::gfx::Camera::Render()
{
	std::list<anjing::core::GameObject*>& game_objects = anjing::core::Scene::GetInstance().game_objects;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto iter = game_objects.begin();
	for (iter; iter != game_objects.end(); ++iter)
	{
		anjing::core::GameObject* go = *iter;

		// check if go has renderer
		anjing::gfx::MeshRenderer* mesh_renderer = go->GetMeshRenderer();
		if (mesh_renderer != nullptr)
		{
			mesh_renderer->Render();
		}
	}

}

anjing::math::Vec3 anjing::gfx::Camera::GetDirection() const
{
	// FIXME: for now always looking at z positive direction
	return anjing::math::Vec3(0, 0, 1);
}

anjing::math::Vec3 anjing::gfx::Camera::GetUp() const
{
	// FIXME: for now always return y + direction
	return anjing::math::Vec3(0, 1, 0);
}

void anjing::gfx::Camera::UpdateProj()
{
	proj_mat = anjing::math::perspective(fovy, aspect_ratio, near_clip, far_clip);
}

void anjing::gfx::Camera::UpdateView()
{
	anjing::core::Transform* transform = this->GetOwner()->GetComponent<anjing::core::Transform>();
	view_mat = anjing::math::LookAt(transform->GetWorldPosition(),
		transform->GetWorldPosition() + GetDirection(), GetUp());
}

void anjing::gfx::Camera::OnAdded()
{
	anjing::core::Scene::GetInstance().SetCamera(this);
	this->Init();
}

void anjing::gfx::Camera::OnRemoved()
{
	anjing::core::Scene::GetInstance().SetCamera(nullptr);
}
