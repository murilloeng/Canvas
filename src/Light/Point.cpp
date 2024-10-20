//canvas
#include "Canvas/inc/Light/Point.hpp"

namespace canvas
{
	namespace lights
	{
		//constructors
		Point::Point(void)
		{
			return;
		}
		
		//destructor
		Point::~Point(void)
		{
			return;
		}

		//data
		vec3 Point::point(void) const
		{
			return m_point;
		}
		vec3 Point::point(vec3 point)
		{
			return m_point = point;
		}

		Color Point::color(void) const
		{
			return m_color;
		}
		Color Point::color(Color color)
		{
			return m_color = color;
		}
	}
}