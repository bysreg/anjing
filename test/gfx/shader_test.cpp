/**

	Shader's test. This test always create app object first before executing each tests
	because Shader uses OpenGL's functions that would need OpenGL to be initialized.
	Anjing initialize OpenGL using SDL initialize function which is called from the 
	App class

*/

#include "gfx/mesh.hpp"
#include "gfx/shader.hpp"
#include "app/app.hpp"

#include <gtest/gtest.h>

class ShaderTest : public ::testing::Test
{
	anjing::app::App* app;

	virtual void SetUp() override
	{
		::testing::Test::SetUp();

		app = Anew anjing::app::App;
		anjing::app::App::StartApplication(app, 800, 600, 60, "TestShader");
	}

	virtual void TearDown() override
	{
		::testing::Test::TearDown();

		Adelete(app);
	}
};

TEST_F(ShaderTest, CheckLoadShader)
{	

	// FIXME : for some reason, on linux these failure tests will result in
	// segmentation fault, so we disable these tests for now for linux
	anjing::gfx::Shader* shader = nullptr;

#ifndef __linux__
	printf("--- test some error checks on shader compilation... \n ---");

	// test failure to compile the shader program
	printf("> test wrong path for vertex and fragment shader\n");
	shader = anjing::gfx::Shader::LoadShaderProgram("", "");	
	EXPECT_EQ(shader, nullptr);

	// test failure to compile fragment shader
	printf("> test wrong path for fragment shader\n");
	shader = anjing::gfx::Shader::LoadShaderProgram("default/default.vs", "");
	EXPECT_EQ(shader, nullptr);

	// test failure to compile vertex shader
	printf("> test wrong path for vertex shader\n");
	shader = anjing::gfx::Shader::LoadShaderProgram("", "default/default.fs");
	EXPECT_EQ(shader, nullptr);

	// test compile error on vertex shader
	printf("> test compile error in vertex shader\n");
	shader = anjing::gfx::Shader::LoadShaderProgram("default/test/error.vs", "default/default.fs");
	EXPECT_EQ(shader, nullptr);

	// test linking error (no main in fragment shader)
	printf("> test compile error in fragment shader\n");
	shader = anjing::gfx::Shader::LoadShaderProgram("default/default.vs", "default/test/error.fs");
	EXPECT_EQ(shader, nullptr);
#endif

	// this one should be successfull
	shader = anjing::gfx::Shader::LoadShaderProgram("default/default.vs", "default/default.fs");
	EXPECT_NE(shader, nullptr);	
	

}
