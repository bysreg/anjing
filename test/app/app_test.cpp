#include "app/app.hpp"

#include <gtest/gtest.h>

TEST(AppTest, NormalUseCase) 
{

	anjing::app::App app;
	EXPECT_EQ(0, anjing::app::App::StartApplication(&app, 800, 600, 60, "My App"));
	
}
