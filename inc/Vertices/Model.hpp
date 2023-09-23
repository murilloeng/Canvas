#pragma once

//canvas
#include "inc/Colors/Color.hpp"
#include "inc/Vertices/Vertex.hpp"
#include "inc/Kinematics/vec3.hpp"

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
			vec3 m_position;
		};
	}
}