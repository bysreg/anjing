#include "gfx/camera.hpp"
#include "app/app.hpp"
#include "core/game_object.hpp"
#include "math/tmat4.hpp"

#include <gtest/gtest.h>

#include <memory>

#define TEST_TITLE CameraTest

using namespace anjing::gfx;
using namespace anjing::app;
using namespace anjing::core;
using namespace anjing::math;

class CameraTest : public ::testing::Test
{

public:

	App* app;
	
	GameObject* cam_go;
	Camera* cam;

	void SetUp() override
	{
		::testing::Test::SetUp();
		app = new App;
		App::StartApplication(app, 800, 600, 60, "TestMeshRenderer");

		cam_go = new GameObject;
		cam_go->AddComponent<Camera>();
		cam = cam_go->GetComponent<Camera>();
	}

	void TearDown() override
	{
		::testing::Test::TearDown();
		
		delete cam_go;

		App::StopApplication(app);
		delete app;
	}

};

TEST_F(TEST_TITLE, DefaultInit)
{
	// check default camera's projection
	Mat4f proj = cam->GetProjMat();
	std::cout << proj << std::endl;

	// check default camera's view
	Mat4f view = cam->GetViewMat();
	std::cout << proj << std::endl;

	EXPECT_TRUE(cam_go != nullptr);
}