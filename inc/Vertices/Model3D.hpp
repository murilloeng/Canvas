#pragma once

//canvas
#include "Canvas/inc/Colors/Color.hpp"
#include "Canvas/inc/Vertices/Vertex3D.hpp"

namespace canvas
{
	namespace vertices
	{
		class Model3D : public Vertex3D
		{
		public:
			//constructor
			Model3D(void);

			//destructor
			~Model3D(void);

			//data
			Color m_color;
		};
	}
}