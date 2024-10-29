#pragma once

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Vertices/Vertex2D.hpp"

namespace canvas
{
	namespace vertices
	{
		class Image2D : public Vertex2D
		{
		public:
			//constructor
			Image2D(void);

			//destructor
			~Image2D(void);

			//attributes
			static void attributes(std::vector<Attribute>&);

			//data
			vec2 m_texture_coordinates;
		};
	}
}