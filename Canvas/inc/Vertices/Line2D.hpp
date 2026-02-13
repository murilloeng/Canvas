#pragma once

//canvas
#include "Canvas/Canvas/inc/Vertices/Model2D.hpp"

namespace canvas
{
	namespace vertices
	{
		class Line2D : public Model2D
		{
		public:
			//constructor
			Line2D(void);

			//destructor
			~Line2D(void);

			//print
			void print(void) const;

			//data
			float m_thickness;
		};
	}
}