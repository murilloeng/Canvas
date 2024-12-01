#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"
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

			//attributes
			static void attributes(std::vector<Attribute>&);

			//data
			Color m_color;
			vec2 m_texture_coordinates;
		};
	}
}