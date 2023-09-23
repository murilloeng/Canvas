#pragma once

//canvas
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"
#include "inc/Kinematics/vec3.hpp"

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

			vec3 position(unsigned) const;
			vec3 position(unsigned, vec3);

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
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			bool m_draw;
			bool m_fill;
			vec3 m_positions[3];
			Color m_draw_colors[3];
			Color m_fill_colors[3];
		};
	}
}