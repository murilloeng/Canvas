#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Vertices/Vertex.hpp"

namespace canvas
{
	namespace vertices
	{
		class Vertex3D : public Vertex
		{
		public:
			//constructor
			Vertex3D(void);

			//destructor
			~Vertex3D(void);

			//data
			vec3 m_position;
		};
	}
}