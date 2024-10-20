//canvas
#include "Canvas/inc/Light/Direction.hpp"

namespace canvas
{
	namespace lights
	{
		//constructor
		Direction::Direction(void)
		{
			return;
		}

		//destructor
		Direction::~Direction(void)
		{
			return;
		}

		//data
		Color Direction::color(void) const
		{
			return m_color;
		}
		Color Direction::color(Color color)
		{
			return m_color = color;
		}

		vec3 Direction::direction(void) const
		{
			return m_direction;
		}
		vec3 Direction::direction(vec3 direction)
		{
			return m_direction = direction;
		}
	}
}