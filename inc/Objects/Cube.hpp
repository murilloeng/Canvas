#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Cube : public Object
		{
		public:
			//constructors
			Cube(void);

			//destructor
			~Cube(void);

			//data
			bool draw(bool);
			bool draw(void) const;

			bool fill(bool);
			bool fill(void) const;

			Color draw_color(unsigned) const;
			Color draw_color(unsigned, Color);

			Color fill_color(unsigned) const;
			Color fill_color(unsigned, Color);

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_draw_data(unsigned**) const;
			void ibo_fill_data(unsigned**) const;
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			bool m_draw;
			bool m_fill;
			Color m_draw_colors[8];
			Color m_fill_colors[8];
		};
	}
}