#pragma once

//canvas
#include "inc/Vertices/Vertex.hpp"

namespace canvas
{
	namespace vertices
	{
		class Model : public Vertex
		{
		public:
			//constructor
			Model(void);

			//destructor
			~Model(void);

			//data
			float m_color[3];
			float m_position[3];
		};
	}
}