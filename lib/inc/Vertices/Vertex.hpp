#pragma once

//canvas
#include "Canvas/lib/inc/Math/vec3.hpp"

namespace canvas
{
	namespace vertices
	{
		class Vertex
		{
		public:
			//constructor
			Vertex(void);

			//destructor
			~Vertex(void);

			//data
			vec3 m_position;
		};
	}
}