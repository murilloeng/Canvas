#pragma once

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
			//buffers
			void vbo_size(uint32_t[]) const override;
			void ibo_size(uint32_t[]) const override;

			//draw
			void ibo_fill_data(uint32_t**) const;
			void ibo_stroke_data(uint32_t**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			vec3 m_center;
			float m_radius;
			float m_height;
			static uint32_t m_mesh;
		};
	}
}