#pragma once

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Colors/Color.hpp"
#include "Canvas/inc/Vertices/Vertex2D.hpp"

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

			//data
			Color m_color;
			vec2 m_texture_coordinates;
		};
	}
}