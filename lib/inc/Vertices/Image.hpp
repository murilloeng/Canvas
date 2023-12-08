#pragma once

//canvas
#include "Canvas/lib/inc/Math/vec2.hpp"
#include "Canvas/lib/inc/Math/vec3.hpp"
#include "Canvas/lib/inc/Vertices/Vertex.hpp"

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