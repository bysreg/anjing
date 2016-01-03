#include "core/game_object.hpp"
#include "core/component.hpp"

#include <gtest/gtest.h>

using namespace anjing;
using namespace anjing::core;

TEST(GameObjectTest, ConstructionCheck)
{
	GameObject* go = Anew GameObject;

	EXPECT_NE(go, nullptr);
}

TEST(GameObjectTest, AddComponentCheck)
{
	GameObject* go = Anew GameObject;
	Component* component = go->AddComponent<Component>();
	
	EXPECT_NE(component, nullptr);
	EXPECT_EQ(go, component->GetOwner());
	EXPECT_NE(go->GetComponent<Component>(), nullptr);
}

TEST(GameObjectTest, AddMeshRendererCheck)
{
	GameObject* go = Anew GameObject;
	Component* mesh_renderer = go->AddComponent<anjing::gfx::MeshRenderer>();

	EXPECT_NE(mesh_renderer, nullptr);
	EXPECT_EQ(mesh_renderer->GetOwner(), go);
	EXPECT_EQ(go->GetComponent<anjing::gfx::MeshRenderer>(), mesh_renderer);
}
