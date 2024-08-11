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
		class Circle : public Geometry
		{
		public:
			//constructors
			Circle(void);

			//destructor
			~Circle(void);

			//data
			vec3 center(void) const;
			vec3 center(const vec3&);

			vec3 normal(void) const;
			vec3 normal(const vec3&);

			float radius(float);
			float radius(void) const;

			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

		protected:
			//buffers
			void fill_data(void) const;
			void stroke_data(void) const;
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			vec3 m_center;
			vec3 m_normal;
			float m_radius;
			static uint32_t m_mesh;
		};
	}
}