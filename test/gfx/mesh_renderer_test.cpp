#include "core/game_object.hpp"
#include "gfx/mesh.hpp"
#include "gfx/mesh_renderer.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;
using namespace anjing::gfx;

class MeshRendererTest : public ::testing::Test
{
public:
	GameObject* go;

	virtual void SetUp() override
	{
		::testing::Test::SetUp();

		go = Anew GameObject;
	}

	virtual void TearDown() override
	{
		::testing::Test::TearDown();

		Adelete(go);
	}
};

TEST_F(MeshRendererTest, Triangle)
{
	MeshRenderer* mesh_renderer = static_cast<MeshRenderer*>(go->AddComponent<MeshRenderer>());

	EXPECT_NE(mesh_renderer, nullptr);
	
	Mesh* mesh = static_cast<Mesh*>(go->AddComponent<Mesh>());
	
}