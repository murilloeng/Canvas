//std
#include <cstdio>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Line.hpp"

namespace canvas
{
	namespace fonts
	{
		//constructor
		Line::Line(void) : m_points{{0, 0}, {0, 0}}
		{
			return;
		}

		//destructor
		Line::~Line(void)
		{
			return;
		}

		//print
		void Line::print(void) const
		{
			printf("Line:\n");
			printf("\tPoint 1: %zd %zd\n", m_points[0][0], m_points[0][1]);
			printf("\tPoint 2: %zd %zd\n", m_points[1][0], m_points[1][1]);
		}
	}
}