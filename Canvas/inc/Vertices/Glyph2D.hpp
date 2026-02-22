#pragma once

//Canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	namespace vertices
	{
		class Glyph2D
		{
		public:
			//constructor
			Glyph2D(void);

			//destructor
			~Glyph2D(void);

			//print
			void print(void) const;

			//data
			Color m_color;
			vec2 m_position[4];
			vec2 m_texture_coordinates[4];
		};
	}
}