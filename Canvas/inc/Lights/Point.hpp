#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"

#include "Canvas/Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	namespace lights
	{
		class Point
		{
		public:
			//constructors
			Point(void);

			//destructor
			~Point(void);

			//data
			vec3 position(vec3);
			vec3 position(void) const;

			Color color(Color);
			Color color(void) const;

		private:
			//data
			vec3 m_position;
			Color m_color;
		};
	}
}