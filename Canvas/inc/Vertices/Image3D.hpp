#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"
#include "Canvas/Canvas/inc/Vertices/Vertex3D.hpp"

namespace canvas
{
	namespace vertices
	{
		class Image3D : public Vertex3D
		{
		public:
			//constructor
			Image3D(void);

			//destructor
			~Image3D(void);

			//attributes
			static void attributes(std::vector<Attribute>&);

			//data
			vec2 m_texture_coordinates;
		};
	}
}