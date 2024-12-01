#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Objects/Geometry.hpp"

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
			//data
			void ibo_fill_data(void) const;
			void vbo_fill_data(void) const;
			void ibo_stroke_data(void) const;
			void vbo_stroke_data(void) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			vec3 m_sizes;
			vec3 m_center;
		};
	}
}