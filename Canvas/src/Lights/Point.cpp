//canvas
#include "Canvas/Canvas/inc/Lights/Point.hpp"

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
		vec3 Point::position(void) const
		{
			return m_position;
		}
		vec3 Point::position(vec3 point)
		{
			return m_position = point;
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