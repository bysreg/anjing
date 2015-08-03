#include "app/app.hpp"

#include <gtest/gtest.h>

using namespace anjing;

TEST(AppTest, NormalUseCase) {

	App app;
	EXPECT_EQ(0, App::StartApplication(&app, 800, 600, 60, "My App"));
	
}
