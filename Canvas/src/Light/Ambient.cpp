//canvas
#include "Canvas/Canvas/inc/Light/Ambient.hpp"

namespace canvas
{
	namespace lights
	{
		//constructors
		Ambient::Ambient(void)
		{
			return;
		}

		//destructor
		Ambient::~Ambient(void)
		{
			return;
		}

		//data
		Color Ambient::color(void) const
		{
			return m_color;
		}
		Color Ambient::color(Color color)
		{
			return m_color = color;
		}
	}
}