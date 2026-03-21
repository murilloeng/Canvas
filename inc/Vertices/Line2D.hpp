#pragma once

//Canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	namespace vertices
	{
		class Line2D
		{
		public:
			//constructor
			Line2D(void);

			//destructor
			~Line2D(void);

			//print
			void print(void) const;

			//data
			Color m_color;
			vec2 m_points[2];
			float m_thickness;
		};
	}
}