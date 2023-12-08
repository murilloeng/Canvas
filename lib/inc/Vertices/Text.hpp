#pragma once

//canvas
#include "Canvas/lib/inc/Math/vec2.hpp"
#include "Canvas/lib/inc/Math/vec3.hpp"
#include "Canvas/lib/inc/Colors/Color.hpp"
#include "Canvas/lib/inc/Vertices/Vertex.hpp"

namespace canvas
{
	namespace vertices
	{
		class Text : public Vertex
		{
		public:
			//constructor
			Text(void);

			//destructor
			~Text(void);

			//data
			Color m_color;
			vec2 m_texture_coordinates;
		};
	}
}