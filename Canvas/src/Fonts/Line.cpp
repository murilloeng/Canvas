//std
#include <cstdio>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Line.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"

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

		//type
		Item::Type Line::type(void) const
		{
			return Item::Type::Line;
		}

		//print
		void Line::print(void) const
		{
			printf("Line:\n");
			printf("\tPoint 1: %zd %zd\n", m_points[0][0], m_points[0][1]);
			printf("\tPoint 2: %zd %zd\n", m_points[1][0], m_points[1][1]);
		}

		//object
		objects::Object* Line::object(void) const
		{
			//data
			objects::Line* line = new objects::Line;
			//setup
			line->point(0, {(float) m_points[0][0], (float) m_points[0][1], 0});
			line->point(1, {(float) m_points[1][0], (float) m_points[1][1], 0});
			//return
			return line;
		}

		//intersect
		float Line:: point(uint32_t index, float t) const
		{
			const double x0 = m_points[0][index];
			const double x1 = m_points[1][index];
			return x0 + (x1 - x0) * t;
		}
		uint32_t Line::hit(const float* origin) const
		{
			//data
			const float xp = origin[0];
			const float yp = origin[1];
			const int64_t y0 = m_points[0][1];
			const int64_t y1 = m_points[1][1];
			//compute
			if(y0 != y1)
			{
				const float t = (yp - y0) / (y1 - y0);
				return t >= 0 && t < 1 && point(0, t) > xp;
			}
			else return yp == y0;
		}
	}
}