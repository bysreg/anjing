#include "app/app.hpp"

#include <gtest/gtest.h>

using anjing;

TEST(AppTest, NormalUseCase) {

	App app;
	EXPECT_EQ(0, App::StartApplication(&app, 800, 600, 60, "My App"));
	
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
