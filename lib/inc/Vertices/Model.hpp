#pragma once

//canvas
#include "Canvas/lib/inc/Math/vec3.hpp"
#include "Canvas/lib/inc/Colors/Color.hpp"
#include "Canvas/lib/inc/Vertices/Vertex.hpp"

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