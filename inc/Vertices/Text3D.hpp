#pragma once

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Colors/Color.hpp"
#include "Canvas/inc/Vertices/Vertex3D.hpp"

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

			//attributes
			static void attributes(std::vector<Attribute>&);

			//data
			Color m_color;
			vec2 m_texture_coordinates;
		};
	}
}