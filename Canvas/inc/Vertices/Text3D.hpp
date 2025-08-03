#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"

#include "Canvas/Canvas/inc/Colors/Color.hpp"

#include "Canvas/Canvas/inc/Vertices/Vertex3D.hpp"

namespace canvas
{
	namespace vertices
	{
		class Text3D : public Vertex3D
		{
		public:
			//constructor
			Text3D(void);

			//destructor
			~Text3D(void);

			//print
			void print(void) const;

			//data
			Color m_color;
			vec2 m_texture_coordinates;
		};
	}
}