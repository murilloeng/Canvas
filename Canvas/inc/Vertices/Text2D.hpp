#pragma once

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"

#include "Canvas/Canvas/inc/Vertices/Vertex2D.hpp"

namespace canvas
{
	namespace vertices
	{
		class Text2D : public Vertex2D
		{
		public:
			//constructor
			Text2D(void);

			//destructor
			~Text2D(void);

			//print
			void print(void) const;

			//data
			Color m_color;
			vec2 m_texture_coordinates;
		};
	}
}