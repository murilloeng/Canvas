#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Triangle : public Geometry
		{
		public:
			//constructors
			Triangle(void);

			//destructor
			~Triangle(void);

			//data
			vec3 point(uint32_t) const;
			vec3 point(uint32_t, const vec3&);

		protected:
			//buffers
			void fill_data(void) const;
			void stroke_data(void) const;
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			vec3 m_points[3];
		};
	}
}