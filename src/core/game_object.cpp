#include "core/game_object.hpp"
#include "core/scene.hpp"

using namespace anjing::core;

GameObject::GameObject() : mesh_renderer(nullptr), transform(nullptr), components(nullptr)
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

bool anjing::core::GameObject::RemoveComponent(anjing::core::Component* component)
{
	for (size_t i = 0; i < components->size(); i++)
	{
		if (components->at(i) == component)
		{
			components->erase(components->begin() + i);
			component->OnRemoved();
			Adelete(component);
			return true;
		}
	}

	return false;
}

void GameObject::RemoveAllComponents()
{
	for (size_t i = 0; i < components->size(); i++)
	{
		Component* component = components->at(i);
		component->OnRemoved();
		Adelete(component);
	}

	components->clear();
}

void GameObject::AddComponentToGOList(Component* component)
{
	component->owner = this;
	components->push_back(component);
	component->OnAdded();
}

void GameObject::Update()
{}
