#pragma once

//Canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"

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
			uint32_t m_dash_type;
			uint32_t m_dash_length;
		};
	}
}