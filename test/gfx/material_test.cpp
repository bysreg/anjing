/**

	Material's test. This test always create app object first before executing each tests
	because Material uses OpenGL's functions that would need OpenGL to be initialized.
	Anjing initialize OpenGL using SDL initialize function which is called from the 
	App class

*/

#include "gfx/shader.hpp"
#include "gfx/material.hpp"
#include "app/app.hpp"

#include <gtest/gtest.h>

class MaterialTest : public ::testing::Test
{
	anjing::app::App* app;
	anjing::gfx::Material* mat;

	virtual void SetUp() override
	{
		::testing::Test::SetUp();

		app = Anew anjing::app::App;
		anjing::app::App::StartApplication(app, 800, 600, 60, "TestShader");

		mat = Anew anjing::gfx::Material;
	}

	virtual void TearDown() override
	{
		::testing::Test::TearDown();

		Adelete(mat);

		anjing::app::App::StopApplication(app);
		Adelete(app);
	}
};

TEST(MaterialTest, CheckConstruction)
{	
	anjing::gfx::Material* mat = Anew anjing::gfx::Material;	
	EXPECT_NE(mat, nullptr);
	Adelete(mat);
}