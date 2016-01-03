#include "game_object.hpp"

using namespace anjing::core;

GameObject::GameObject() : components(nullptr)
{
	components = Anew std::vector<Component*>();
	components->reserve(2);
}

GameObject::~GameObject()
{	
	RemoveAllComponents();
	Adelete(components);
}

void GameObject::RemoveAllComponents()
{
	for (size_t i = 0; i < components->size(); i++)
	{
		Component* component = components->at(i);
		Adelete(component);
	}
}

void GameObject::AddComponentToGOList(Component* component)
{
	component->owner = this;
	components->push_back(component);
}

void GameObject::Update()
{
}
