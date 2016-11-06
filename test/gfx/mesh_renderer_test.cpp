#include "core/game_object.hpp"
#include "gfx/mesh.hpp"
#include "gfx/mesh_renderer.hpp"
#include "math/tvec3.hpp"
#include "gfx/material.hpp"
#include "gfx/shader.hpp"
#include "app/app.hpp"
#include "core/scene.hpp"
#include "gfx/camera.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;
using namespace anjing::gfx;
using namespace anjing::math;

class MeshRendererTest : public ::testing::Test
{
public:
	GameObject* go;
	GameObject* mainCamera;
	anjing::app::App* app;

	virtual void SetUp() override
	{
		::testing::Test::SetUp();

		// need to start the application first, before we can render anything
		app = Anew anjing::app::App;
		anjing::app::App::StartApplication(app, 800, 600, 60, "TestMeshRenderer");

		go = Anew GameObject;

		// a scene has to have one gameobject as camera to be able to display anything
		mainCamera = Anew GameObject;
		mainCamera->AddComponent<anjing::gfx::Camera>();
	}

	virtual void TearDown() override
	{
		::testing::Test::TearDown();

		Adelete(go);
		Adelete(mainCamera);

		anjing::app::App::StopApplication(app);
		Adelete(app);
	}
};

TEST_F(MeshRendererTest, Triangle)
{
	MeshRenderer* mesh_renderer = static_cast<MeshRenderer*>(go->AddComponent<MeshRenderer>());
	EXPECT_NE(mesh_renderer, nullptr);

	Mesh mesh;

	EXPECT_EQ(mesh.IsDirty(), true);

	mesh.AddVertex(Vertex(Vec3f(0, 0, 0), Vec4f(1, 0, 0, 1)));
	mesh.AddVertex(Vertex(Vec3f(1, 0, 0), Vec4f(0, 1, 0, 1)));
	mesh.AddVertex(Vertex(Vec3f(0, 1, 0), Vec4f(0, 0, 1, 1)));

	EXPECT_EQ(mesh.GetVertexCount(), 3u);

	mesh.AddIndex(0);
	mesh.AddIndex(1);
	mesh.AddIndex(2);

	EXPECT_EQ(mesh.GetIndexCount(), 3u);
	EXPECT_EQ(mesh.IsDirty(), true);

	mesh.UpdateMesh();
	EXPECT_EQ(mesh.IsDirty(), false);

	anjing::gfx::Shader* shader = anjing::gfx::Shader::LoadShaderProgram("default/default.vs", "default/default.fs");

	anjing::gfx::Material* mat = Anew anjing::gfx::Material;
	mat->SetShader(shader);

	mesh_renderer->SetMaterial(mat);
	mesh_renderer->SetMesh(&mesh);

	anjing::core::Scene::GetInstance().Render();
}
