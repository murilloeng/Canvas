#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Cube : public Geometry
		{
		public:
			//constructors
			Cube(void);

			//destructor
			~Cube(void);

			//data
			vec3 sizes(void) const;
			vec3 sizes(const vec3&);

			vec3 center(void) const;
			vec3 center(const vec3&);

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
			vec3 m_sizes;
			vec3 m_center;
		};
	}
}