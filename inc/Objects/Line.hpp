#pragma once

//canvas
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Line : public Object
		{
		public:
			//constructors
			Line(void);

			//destructor
			~Line(void);

			//data
			const float* color(unsigned) const;
			float* color(unsigned, const float*);
			float* color(unsigned, float, float, float);

			const float* position(unsigned) const;
			float* position(unsigned, const float*);
			float* position(unsigned, float, float, float);

			//type
			objects::type type(void) const override;

			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			float m_colors[2][3];
			float m_positions[2][3];
		};
	}
}