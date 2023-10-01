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
			vec3 sizes(vec3);
			vec3 sizes(void) const;

			vec3 center(vec3);
			vec3 center(void) const;

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
			void vbo_draw_data(vertices::Vertex*) const;
			void vbo_fill_data(vertices::Vertex*) const;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_sizes;
			vec3 m_center;
			Color m_draw_colors[8];
			Color m_fill_colors[8];
		};
	}
}