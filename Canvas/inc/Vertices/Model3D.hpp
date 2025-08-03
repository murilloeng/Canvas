#pragma once

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"

#include "Canvas/Canvas/inc/Vertices/Vertex3D.hpp"

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

			//print
			void print(void) const;

			//data
			Color m_color;
		};
	}
}