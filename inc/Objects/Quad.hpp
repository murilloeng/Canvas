#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Quad : public Object
		{
		public:
			//constructors
			Quad(void);

			//destructor
			~Quad(void);

			//data
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
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_positions[4];
			Color m_draw_colors[4];
			Color m_fill_colors[4];
		};
	}
}