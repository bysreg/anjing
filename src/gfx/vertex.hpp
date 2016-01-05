#pragma once

#include "math/tvec3.hpp"
#include "math/tvec4.hpp"
#include "math/tvec2.hpp"

namespace anjing
{
	namespace gfx
	{
		struct Vertex
		{
			anjing::math::Vec3 pos;
			anjing::math::Vec4 color;
			anjing::math::Vec2 tex_coord;
			anjing::math::Vec3 normal;

			///
			/// Default	constructor for Vertex
			///
			Vertex() {}

			///
			/// Constructor for Vertex that receives Vec3 position and Vec4 color as input
			///
			Vertex(const anjing::math::Vec3& pos, const anjing::math::Vec4& color) : pos(pos), color(color)				
			{}
		};
	}
}