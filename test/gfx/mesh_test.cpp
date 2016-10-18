#include "gfx/mesh.hpp"

#include <gtest/gtest.h>

using namespace anjing::core;
using namespace anjing::gfx;
using namespace anjing::math;

TEST(MeshTest, SimpleColorTriangle)
{
	Mesh mesh;

	mesh.AddVertex(Vertex(Vec3f(0, 0, 0), Vec4f(1, 0, 0, 1)));
	mesh.AddVertex(Vertex(Vec3f(1, 0, 0), Vec4f(0, 1, 0, 1)));
	mesh.AddVertex(Vertex(Vec3f(0, 1, 0), Vec4f(0, 0, 1, 1)));
	mesh.AddIndex(0);
	mesh.AddIndex(1);
	mesh.AddIndex(2);

	EXPECT_EQ(mesh.GetVertexCount(), 3);
	EXPECT_EQ(mesh.GetIndexCount(), 3);
}
