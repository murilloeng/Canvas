#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Colors/Color.hpp"

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
			vec3 point(vec3);
			vec3 point(void) const;

			Color color(Color);
			Color color(void) const;

		private:
			//data
			vec3 m_point;
			Color m_color;
		};
	}
}