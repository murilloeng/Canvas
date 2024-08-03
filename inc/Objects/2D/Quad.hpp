#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Quad : public Geometry
		{
		public:
			//constructors
			Quad(void);

			//destructor
			~Quad(void);

			//data
			vec3 point(uint32_t) const;
			vec3 point(uint32_t, const vec3&);

		protected:
			//data
			void ibo_fill_data(uint32_t**) const;
			void ibo_stroke_data(uint32_t**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			vec3 m_points[4];
		};
	}
}