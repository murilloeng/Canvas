#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Palette : public Object
		{
		public:
			//constructors
			Palette(void);

			//destructor
			~Palette(void);

		protected:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
		};
	}
}