#pragma once

//canvas
#include "inc/Math/vec2.hpp"
#include "inc/Math/vec3.hpp"
#include "inc/Colors/Color.hpp"
#include "inc/Vertices/Vertex.hpp"

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