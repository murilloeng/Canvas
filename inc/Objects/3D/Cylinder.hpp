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
		class Cylinder : public Geometry
		{
		public:
			//constructors
			Cylinder(void);

			//destructor
			~Cylinder(void);

			//data
			vec3 center(void) const;
			vec3 center(const vec3&);

			float radius(float);
			float radius(void) const;

			float height(float);
			float height(void) const;

			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

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
			vec3 m_center;
			float m_radius;
			float m_height;
			static uint32_t m_mesh;
		};
	}
}