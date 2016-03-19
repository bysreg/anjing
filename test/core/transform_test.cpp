#include "core/transform.hpp"
#include "core/game_object.hpp"

#include <gtest/gtest.h>

class TransformTest : public ::testing::Test
{

protected:

	anjing::core::GameObject* go;

	virtual void SetUp() override
	{
		::testing::Test::SetUp();

		go = Anew anjing::core::GameObject;
	}

	virtual void TearDown() override
	{
		::testing::Test::TearDown();		
		Adelete(go);
	}
};

TEST_F(TransformTest, ConstructionCheck)
{
	EXPECT_NE(go, nullptr);
	EXPECT_NE(go->GetTransform(), nullptr);
}
