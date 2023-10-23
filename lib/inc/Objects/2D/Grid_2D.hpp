#pragma once

//canvas
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
			unsigned mesh(unsigned) const;
			unsigned mesh(unsigned, unsigned);

		protected:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			unsigned m_mesh[2];

			//friends
			friend class Grid_3D;
		};
	}
}