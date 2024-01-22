#pragma once

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Vertices/Vertex.hpp"

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
			vec2 m_texture_coordinates;
		};
	}
}