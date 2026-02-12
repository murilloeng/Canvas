//std
#include <cmath>
#include <cstdio>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Conic.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Bezier.hpp"

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

		//type
		Item::Type Conic::type(void) const
		{
			return Item::Type::Conic;
		}

		//print
		void Conic::print(void) const
		{
			printf("Conic:\n");
			printf("\tPoint 1: %zd %zd\n", m_points[0][0], m_points[0][1]);
			printf("\tPoint 2: %zd %zd\n", m_points[1][0], m_points[1][1]);
			printf("\tControl: %zd %zd\n", m_control[0], m_control[1]);
		}

		//object
		objects::Object* Conic::object(void) const
		{
			//data
			objects::Bezier* bezier = new objects::Bezier;
			//setup
			bezier->type(objects::Bezier::Type::Conic);
			bezier->control(0, {(float) m_control[0], (float) m_control[1], 0});
			bezier->point(0, {(float) m_points[0][0], (float) m_points[0][1], 0});
			bezier->point(1, {(float) m_points[1][0], (float) m_points[1][1], 0});
			//return
			return bezier;
		}

		//intersect
		uint32_t Conic::hit(const float* origin) const
		{
			//data
			const float xp = origin[0];
			const float yp = origin[1];
			const float y1 = m_control[1];
			const float y0 = m_points[0][1];
			const float y2 = m_points[1][1];
			//compute
			const float c = y0 - yp;
			const float b = 2 * (y1 - y0);
			const float a = y0 + y2 - 2 * y1;
			const float d = b * b - 4 * a * c;
			if(d < 0) return 0;
			const float t1 = -(b + sqrtf(d)) / a / 2;
			const float t2 = -(b - sqrtf(d)) / a / 2;
			return (t1 >= 0 && t1 < 1 && point(0, t1) > xp) + (t2 >= 0 && t2 < 1 && point(0, t2) > xp);
		}
		float Conic::point(uint32_t index, float t) const
		{
			//data
			const double x1 = m_control[index];
			const double x0 = m_points[0][index];
			const double x2 = m_points[1][index];
			//return
			return (x0 + x2 - 2 * x1) * t * t + 2 * (x1 - x0) * t + x0;
		}
	}
}