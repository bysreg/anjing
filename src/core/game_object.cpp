#include "core/game_object.hpp"
#include "core/transform.hpp"
#include "core/scene.hpp"

using namespace anjing::core;

GameObject::GameObject() : components(nullptr), mesh_renderer(nullptr)
{
	components = Anew std::vector<Component*>();
	components->reserve(2);

	// every GameObject has transform component
	AddComponent<Transform>();

	// add the GameObject to the scene
	Scene::GetInstance().AddGameObject(this);
}

GameObject::~GameObject()
{	
	RemoveAllComponents();
	Adelete(components);

	// remove GameObject from the scene
	Scene::GetInstance().RemoveGameObject(this);
}

void GameObject::RemoveAllComponents()
{
	for (size_t i = 0; i < components->size(); i++)
	{
		Component* component = components->at(i);
		Adelete(component);
	}

	components->clear();
}

void GameObject::AddComponentToGOList(Component* component)
{
	component->owner = this;
	components->push_back(component);
}

void GameObject::Update()
{}
