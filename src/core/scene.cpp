#include "core/scene.hpp"
#include "core/game_object.hpp"
#include "gfx/camera.hpp"

anjing::core::Scene::Scene()
{}

void anjing::core::Scene::Render()
{
	m_Camera->Render();
}

void anjing::core::Scene::AddGameObject(GameObject* go)
{
	m_GameObjects.push_back(go);
}

void anjing::core::Scene::RemoveGameObject(GameObject * go)
{
	m_GameObjects.remove(go);
}
