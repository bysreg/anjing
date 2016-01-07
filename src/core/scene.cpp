#include "core/scene.hpp"
#include "core/game_object.hpp"

anjing::core::Scene::Scene()
{}

void anjing::core::Scene::Render()
{
	auto iter = game_objects.begin();
	for (iter; iter != game_objects.end(); ++iter)
	{
		GameObject* go = *iter;

		// check if go has renderer
		anjing::gfx::MeshRenderer* mesh_renderer = go->GetMeshRenderer();
		if (mesh_renderer != nullptr)
		{
			mesh_renderer->Render();
		}
	}
}