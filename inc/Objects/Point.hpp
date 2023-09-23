#pragma once

//canvas
#include "inc/Colors/Color.hpp"
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
			Color color(Color);
			Color color(void) const;

			const float* position(void) const;
			const float* position(const float*);
			const float* position(float, float, float);

			//type
			objects::type type(void) const override;

			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			Color m_color;
			float m_position[3];
		};
	}
}