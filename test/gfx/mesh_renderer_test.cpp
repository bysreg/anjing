#include "core/game_object.hpp"
#include "gfx/mesh.hpp"
#include "gfx/mesh_renderer.hpp"
#include "math/tvec3.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;
using namespace anjing::gfx;
using namespace anjing::math;

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

	Mesh mesh;
	mesh.AddVertex(Vertex(Vec3(0, 0, 0), Vec4(1, 0, 0, 1)));
	mesh.AddVertex(Vertex(Vec3(1, 0, 0), Vec4(0, 1, 0, 1)));
	mesh.AddVertex(Vertex(Vec3(0, 1, 0), Vec4(0, 0, 1, 1)));

	EXPECT_EQ(mesh.GetVertexCount(), 3);

	mesh.AddIndex(0);
	mesh.AddIndex(1);
	mesh.AddIndex(2);

	EXPECT_EQ(mesh.GetIndexCount(), 3);

	/// \todo Test Triangle rendering
}