#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

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
			uint32_t vbo_size(uint32_t) const override;
			uint32_t ibo_size(uint32_t) const override;

			//draw
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			vec3 m_position;
		};
	}
}