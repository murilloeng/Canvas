#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Colors/Color.hpp"
#include "Canvas/inc/Vertices/Vertex.hpp"

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
			Color m_color;
		};
	}
}