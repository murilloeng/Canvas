//std
#include <cstdio>

//Canvas
#include "Canvas/Canvas/inc/Vertices/Glyph2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Glyph2D::Glyph2D(void)
		{
			return;
		}

		//destructor
		Glyph2D::~Glyph2D(void)
		{
			return;
		}

		//print
		void Glyph2D::print(void) const
		{
			m_color.print("Color");
			m_position[0].print("Position 0:");
			m_position[1].print("Position 1:");
			m_position[2].print("Position 2:");
			m_position[3].print("Position 3:");
			m_texture_coordinates[0].print("Texture Coordinates 0:");
			m_texture_coordinates[1].print("Texture Coordinates 1:");
			m_texture_coordinates[2].print("Texture Coordinates 2:");
			m_texture_coordinates[3].print("Texture Coordinates 3:");
		}
	}
}