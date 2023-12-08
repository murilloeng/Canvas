#pragma once

//canvas
#include "Canvas/lib/inc/Math/vec3.hpp"
#include "Canvas/lib/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Point : public Geometry
		{
		public:
			//constructors
			Point(void);

			//destructor
			~Point(void);

			//data
			vec3 position(void) const;
			vec3 position(const vec3&);

		protected:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			vec3 m_position;
		};
	}
}