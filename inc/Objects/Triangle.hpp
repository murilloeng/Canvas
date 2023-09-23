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

			//data
			bool draw(bool);
			bool draw(void) const;

			bool fill(bool);
			bool fill(void) const;

			const float* draw_color(void) const;
			const float* fill_color(void) const;

			float* draw_color(const float*);
			float* draw_color(float, float, float);

			float* fill_color(const float*);
			float* fill_color(float, float, float);

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
			bool m_draw;
			bool m_fill;
			float m_draw_color[3];
			float m_fill_color[3];
			float m_positions[3][3];
		};
	}
}