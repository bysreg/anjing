#include "core/scene.hpp"
#include "core/game_object.hpp"
#include "gfx/camera.hpp"

anjing::core::Scene::Scene()
{}

void anjing::core::Scene::Render()
{
	camera->Render();
}

void anjing::core::Scene::AddGameObject(GameObject* go)
{
	gameobjects.push_back(go);
}

void anjing::core::Scene::RemoveGameObject(GameObject * go)
{
	gameobjects.remove(go);
}
