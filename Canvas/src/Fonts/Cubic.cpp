//std
#include <cstdio>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Cubic.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Bezier.hpp"

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

		//type
		Item::Type Cubic::type(void) const
		{
			return Item::Type::Cubic;
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

		//object
		objects::Object* Cubic::object(void) const
		{
			//data
			objects::Bezier* bezier = new objects::Bezier;
			//setup
			bezier->type(objects::Bezier::Type::Conic);
			bezier->point(0, {(float) m_points[0][0], (float) m_points[0][1], 0});
			bezier->point(1, {(float) m_points[1][0], (float) m_points[1][1], 0});
			bezier->control(0, {(float) m_controls[0][0], (float) m_controls[0][1], 0});
			bezier->control(1, {(float) m_controls[1][0], (float) m_controls[1][1], 0});
			//return
			return bezier;
		}

		//intersect
		uint32_t Cubic::hit(const float* origin) const
		{
			return 0;
		}
		float Cubic::point(uint32_t index, float t) const
		{
			return false;
		}
	}
}