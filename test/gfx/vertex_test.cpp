#include "gfx/vertex.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;
using namespace anjing::gfx;

TEST(VertexTest, CheckVertexStructure)
{
	EXPECT_EQ(std::is_standard_layout<Vertex>::value, true);

	anjing::gfx::Vertex v;

	EXPECT_EQ(offsetof(Vertex, pos), v.GetPosOffset());
	EXPECT_EQ(offsetof(Vertex, color), v.GetColorOffset());
	EXPECT_EQ(offsetof(Vertex, tex_coord), v.GetTexCoordOffset());
	EXPECT_EQ(offsetof(Vertex, normal), v.GetNormalOffset());
}
