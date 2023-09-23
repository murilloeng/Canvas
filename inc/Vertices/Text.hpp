#pragma once

//canvas
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
			float m_texture[2];
			float m_position[3];
		};
	}
}