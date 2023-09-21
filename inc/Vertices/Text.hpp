#pragma once

//canvas
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
			float m_color[3];
			float m_texture[2];
			float m_position[3];
		};
	}
}