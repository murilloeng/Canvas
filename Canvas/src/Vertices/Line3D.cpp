//std
#include <cstdio>

//canvas
#include "Canvas/Canvas/inc/Vertices/Line3D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Line3D::Line3D(void)
		{
			return;
		}

		//destructor
		Line3D::~Line3D(void)
		{
			return;
		}

		//print
		void Line3D::print(void) const
		{
			Model3D::print();
			printf("Thickness: %+.2e\n", m_thickness);
		}
	}
}