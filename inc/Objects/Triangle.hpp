#pragma once

//canvas
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Triangle : public Object
		{
		public:
			//constructors
			Triangle(void);

			//destructor
			~Triangle(void);

			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			float m_colors[3][3];
			float m_positions[3][3];
		};
	}
}