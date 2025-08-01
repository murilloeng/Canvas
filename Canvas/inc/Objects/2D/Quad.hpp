#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"

#include "Canvas/Canvas/inc/Objects/Geometry.hpp"

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
			void ibo_fill_data(void) const;
			void vbo_fill_data(void) const;
			void ibo_stroke_data(void) const;
			void vbo_stroke_data(void) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			vec3 m_points[4];
		};
	}
}