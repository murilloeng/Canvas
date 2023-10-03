#pragma once

//canvas
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"
#include "inc/Objects/Grid_2D.hpp"

namespace canvas
{
	namespace objects
	{
		class Grid_3D : public Object
		{
		public:
			//constructors
			Grid_3D(void);

			//destructor
			~Grid_3D(void);

			//data
			bool fill(bool) override;
			bool stroke(bool) override;

			void fill_color(const Color&);
			void fill_color(const Color&, unsigned);

			void stroke_color(const Color&);
			void stroke_color(const Color&, unsigned);

			unsigned mesh(unsigned) const;
			unsigned mesh(unsigned, unsigned);

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void vbo_affine(vertices::Vertex*) const;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			Grid_2D* m_grids;
			unsigned m_mesh[3];
		};
	}
}