//std
#include <cstdio>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Cubic.hpp"

namespace canvas
{
	namespace fonts
	{
		//constructor
		Cubic::Cubic(void) : m_points{{0, 0}, {0, 0}}, m_controls{{0, 0}, {0, 0}}
		{
			return;
		}

		//destructor
		Cubic::~Cubic(void)
		{
			return;
		}

		//print
		void Cubic::print(void) const
		{
			printf("Cubic:\n");
			printf("\tPoint 1: %zd %zd\n", m_points[0][0], m_points[0][1]);
			printf("\tPoint 2: %zd %zd\n", m_points[1][0], m_points[1][1]);
			printf("\tControl 1: %zd %zd\n", m_controls[0][0], m_controls[0][1]);
			printf("\tControl 2: %zd %zd\n", m_controls[1][0], m_controls[1][1]);
		}
	}
}