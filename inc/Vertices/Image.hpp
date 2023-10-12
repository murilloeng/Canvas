#pragma once

//canvas
#include "inc/Math/vec2.hpp"
#include "inc/Math/vec3.hpp"
#include "inc/Vertices/Vertex.hpp"

namespace canvas
{
	namespace vertices
	{
		class Image : public Vertex
		{
		public:
			//constructor
			Image(void);

			//destructor
			~Image(void);

			//data
			vec2 m_texture;
			vec3 m_position;
		};
	}
}