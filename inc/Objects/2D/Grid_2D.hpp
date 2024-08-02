#pragma once

//canvas
#include "Canvas/inc/Objects/Geometry.hpp"

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
		class Grid_2D : public Geometry
		{
		public:
			//constructors
			Grid_2D(void);

			//destructor
			~Grid_2D(void);

			//data
			uint32_t mesh(uint32_t) const;
			uint32_t mesh(uint32_t, uint32_t);

		protected:
			//buffers
			void vbo_size(uint32_t[]) const override;
			void ibo_size(uint32_t[]) const override;

			//draw
			void ibo_fill_data(uint32_t**) const;
			void ibo_stroke_data(uint32_t**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			uint32_t m_mesh[2];

			//friends
			friend class Grid_3D;
		};
	}
}