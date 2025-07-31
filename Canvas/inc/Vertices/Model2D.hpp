#pragma once

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Vertices/Vertex2D.hpp"

namespace canvas
{
	namespace vertices
	{
		class Model2D : public Vertex2D
		{
		public:
			//constructor
			Model2D(void);

			//destructor
			~Model2D(void);

			//data
			Color m_color;
		};
	}
}