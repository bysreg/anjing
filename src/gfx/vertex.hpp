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
			anjing::math::Vec3f pos;
			anjing::math::Vec4f color;
			anjing::math::Vec2f tex_coord;
			anjing::math::Vec3f normal;

			///
			/// Default	constructor for Vertex
			///
			Vertex() {}

			///
			/// Constructor for Vertex that receives Vec3f position and Vec4f color as input
			///
			Vertex(const anjing::math::Vec3f& new_pos, const anjing::math::Vec4f& new_color) : pos(new_pos), color(new_color)				
			{}

			inline uint16_t GetPosOffset() const { return 0; }
			inline uint16_t GetColorOffset() const { return sizeof(anjing::math::Vec3f); }
			inline uint16_t GetTexCoordOffset() const { return sizeof(anjing::math::Vec4f) + sizeof(anjing::math::Vec3f); }
			inline uint16_t GetNormalOffset() const { return sizeof(anjing::math::Vec2f) + sizeof(anjing::math::Vec4f) + sizeof(anjing::math::Vec3f); }

		};
	}
}
