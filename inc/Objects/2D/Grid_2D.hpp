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
			//data
			void ibo_fill_data(void) const;
			void vbo_fill_data(void) const;
			void ibo_stroke_data(void) const;
			void vbo_stroke_data(void) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			uint32_t m_mesh[2];

			//friends
			friend class Grid_3D;
		};
	}
}