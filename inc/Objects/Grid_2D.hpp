#pragma once

//canvas
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Grid_3D;
	}
}

namespace canvas
{
	namespace objects
	{
		class Grid_2D : public Object
		{
		public:
			//constructors
			Grid_2D(void);

			//destructor
			~Grid_2D(void);

			//data
			Color draw_color(Color);
			Color draw_color(void) const;

			Color fill_color(Color);
			Color fill_color(void) const;

			unsigned mesh(unsigned) const;
			unsigned mesh(unsigned, unsigned);

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
			Color m_draw_color;
			Color m_fill_color;
			unsigned m_mesh[2];

			//friends
			friend class Grid_3D;
		};
	}
}