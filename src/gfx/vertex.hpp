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
			anjing::math::Vec3f m_Pos;
			anjing::math::Vec4f m_Color;
			anjing::math::Vec2f m_TexCoord;
			anjing::math::Vec3f m_Normal;

			///
			/// Default	constructor for Vertex
			///
			Vertex() {}

			///
			/// Constructor for Vertex that receives Vec3f position and Vec4f color as input
			///
			Vertex(const anjing::math::Vec3f& pos, const anjing::math::Vec4f& color) : m_Pos(pos), m_Color(color)				
			{}

			inline uint16_t GetPosOffset() const { return 0; }
			inline uint16_t GetColorOffset() const { return sizeof(anjing::math::Vec3f); }
			inline uint16_t GetTexCoordOffset() const { return sizeof(anjing::math::Vec4f) + sizeof(anjing::math::Vec3f); }
			inline uint16_t GetNormalOffset() const { return sizeof(anjing::math::Vec2f) + sizeof(anjing::math::Vec4f) + sizeof(anjing::math::Vec3f); }

		};
	}
}
