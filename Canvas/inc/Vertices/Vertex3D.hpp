#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Vertices/Vertex.hpp"

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

			//attributes
			static void attributes(std::vector<Attribute>&);

			//data
			vec3 m_position;
		};
	}
}