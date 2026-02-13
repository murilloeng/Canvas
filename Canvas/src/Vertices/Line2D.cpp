//std
#include <cstdio>

//canvas
#include "Canvas/Canvas/inc/Vertices/Line2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Line2D::Line2D(void)
		{
			return;
		}

		//destructor
		Line2D::~Line2D(void)
		{
			return;
		}

		//print
		void Line2D::print(void) const
		{
			Model2D::print();
			printf("Thickness: %+.2e\n", m_thickness);
		}
	}
}