#pragma once

//canvas
#include "inc/Colors/Color.hpp"
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

			Color draw_color(unsigned) const;
			Color draw_color(unsigned, Color);

			Color fill_color(unsigned) const;
			Color fill_color(unsigned, Color);

			const float* position(unsigned) const;
			const float* position(unsigned, const float*);
			const float* position(unsigned, float, float, float);

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			bool m_draw;
			bool m_fill;
			Color m_draw_colors[3];
			Color m_fill_colors[3];
			float m_positions[3][3];
		};
	}
}