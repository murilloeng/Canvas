#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"

#include "Canvas/Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	namespace lights
	{
		class Direction
		{
		public:
			//constructor
			Direction(void);

			//destructor
			~Direction(void);

			//data
			Color color(Color);
			Color color(void) const;

			vec3 direction(vec3);
			vec3 direction(void) const;

		private:
			//data
			Color m_color;
			vec3 m_direction;
		};
	}
}