#pragma once

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Vertices/Vertex.hpp"

namespace canvas
{
	namespace vertices
	{
		class Vertex2D : public Vertex
		{
		public:
			//constructor
			Vertex2D(void);

			//destructor
			~Vertex2D(void);

			//data
			vec2 m_position;
		};
	}
}