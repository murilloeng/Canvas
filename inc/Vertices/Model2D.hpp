#pragma once

//canvas
#include "Canvas/inc/Colors/Color.hpp"
#include "Canvas/inc/Vertices/Vertex2D.hpp"

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

			//attributes
			static void attributes(std::vector<Attribute>&);

			//data
			Color m_color;
		};
	}
}