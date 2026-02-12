//std
#include <cstdio>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Conic.hpp"

namespace canvas
{
	namespace fonts
	{
		//constructor
		Conic::Conic(void) : m_control{0, 0}, m_points{{0, 0}, {0, 0}}
		{
			return;
		}

		//destructor
		Conic::~Conic(void)
		{
			return;
		}

		//print
		void Conic::print(void) const
		{
			printf("Conic:\n");
			printf("\tPoint 1: %zd %zd\n", m_points[0][0], m_points[0][1]);
			printf("\tPoint 2: %zd %zd\n", m_points[1][0], m_points[1][1]);
			printf("\tControl: %zd %zd\n", m_control[0], m_control[1]);
		}
	}
}