//std
#include <cstdio>

//Canvas
#include "Canvas/Canvas/inc/Vertices/Line2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Line2D::Line2D(void) : m_dash_type{0}, m_dash_length{20}
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
			m_color.print("Color");
			m_points[0].print("Point 0:");
			m_points[1].print("Point 1:");
			printf("Thickness: %+.2e\nDash Type: %d\nDash Lenght: %d\n", m_thickness, m_dash_type, m_dash_length);
		}
	}
}