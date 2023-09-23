#pragma once

//canvas
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Point : public Object
		{
		public:
			//constructors
			Point(void);

			//destructor
			~Point(void);

			//data
			const float* color(void) const;
			const float* position(void) const;

			float* color(const float*);
			float* color(float, float, float);

			float* position(const float*);
			float* position(float, float, float);

			//type
			objects::type type(void) const override;

			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			float m_color[3];
			float m_position[3];
		};
	}
}