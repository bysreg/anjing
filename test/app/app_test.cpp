#include "app/app.hpp"

#include <gtest/gtest.h>

TEST(AppTest, NormalUseCase) 
{
	anjing::app::App app;
	EXPECT_EQ(0, anjing::app::App::StartApplication(&app, 800, 600, 60, "My App"));	
	EXPECT_EQ(0, anjing::app::App::StopApplication(&app));
}

TEST(AppTest, CheckGetAssets)
{
	std::FILE* file = anjing::app::App::GetAssets("default/default.vs", "rb");
	EXPECT_NE(file, nullptr);
}