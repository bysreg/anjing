#include "app/app.hpp"
#include "core/memory_manager.hpp"
#include "core/util.hpp"
#include "core/scene.hpp"
#include "core/game_object.hpp"
#include "gfx/mesh.hpp"
#include "gfx/shader.hpp"
#include "gfx/material.hpp"
#include "math/tvec3.hpp"

#include <cstdio>
#include <cstdlib>

static bool auto_close = false;

static bool ParseArgs(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'y':
				auto_close = true;
				break;
			}
		}		
	}

	return true;
}

static void GameLoop()
{
	anjing::core::Scene::GetInstance().Render();
}

static void SetupScene()
{
	using namespace anjing::core;
	using namespace anjing::gfx;
	using namespace anjing::math;

	auto go = Anew GameObject;
	auto mainCamera = Anew GameObject;
	mainCamera->AddComponent<Camera>();

	MeshRenderer* mesh_renderer = static_cast<MeshRenderer*>(go->AddComponent<MeshRenderer>());

	Mesh* mesh = Anew Mesh;

	mesh->AddVertex(Vertex(Vec3f(0, 0, 0), Vec4f(1, 0, 0, 1)));
	mesh->AddVertex(Vertex(Vec3f(1, 0, 0), Vec4f(0, 1, 0, 1)));
	mesh->AddVertex(Vertex(Vec3f(0, 1, 0), Vec4f(0, 0, 1, 1)));

	mesh->AddIndex(0);
	mesh->AddIndex(1);
	mesh->AddIndex(2);

	mesh->UpdateMesh();

	Shader* shader = Shader::LoadShaderProgram("default/default.vs", "default/default.fs");

	Material* mat = Anew Material;
	mat->SetShader(shader);

	mesh_renderer->SetMaterial(mat);
	mesh_renderer->SetMesh(mesh);
}

int main(int argc, char* argv[])
{
	if (!ParseArgs(argc, argv))
	{
		return EXIT_FAILURE;
	}

	anjing::app::App app;
	anjing::app::App::StartApplication(&app, 800, 600, 60, "My App");

	SetupScene();
	anjing::app::App::RunMainLoop(&app, GameLoop);

	anjing::core::MemoryManager::GetInstance().Dump();

	anjing::app::App::StopApplication(&app);

	if (!auto_close)
	{
		printf("Press any key to close ...\n");
		int _ = getchar();
		ANJING_UNUSED(_);
	}

	return 0;
}