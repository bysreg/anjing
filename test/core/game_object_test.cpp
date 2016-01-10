#include "core/game_object.hpp"
#include "core/component.hpp"

#include <gtest/gtest.h>

class GameObjectTest : public ::testing::Test
{
protected:

	anjing::core::GameObject* go;

	virtual void SetUp() override
	{
		::testing::Test::SetUp();

		go = Anew anjing::core::GameObject;
	}

	virtual void TearDown() override
	{
		::testing::Test::TearDown();

		Adelete(go);
	}
};

TEST_F(GameObjectTest, ConstructionCheck)
{
	EXPECT_NE(go, nullptr);
}

TEST_F(GameObjectTest, AddComponentCheck)
{	
	anjing::core::Component* component = go->AddComponent<anjing::core::Component>();
	
	EXPECT_NE(component, nullptr);
	EXPECT_EQ(go, component->GetOwner());
	EXPECT_NE(go->GetComponent<anjing::core::Component>(), nullptr);
}

TEST_F(GameObjectTest, AddMeshRendererCheck)
{
	anjing::core::GameObject* go = Anew anjing::core::GameObject;
	anjing::core::Component* mesh_renderer = go->AddComponent<anjing::gfx::MeshRenderer>();

	EXPECT_NE(mesh_renderer, nullptr);
	EXPECT_EQ(mesh_renderer->GetOwner(), go);
	EXPECT_EQ(go->GetComponent<anjing::gfx::MeshRenderer>(), mesh_renderer);
}
