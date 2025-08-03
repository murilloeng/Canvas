#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"

#include "Canvas/Canvas/inc/Colors/Color.hpp"

#include "Canvas/Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Rectangle : public Geometry
		{
		public:
			//constructor
			Rectangle(void);

			//destructor
			~Rectangle(void);

			//data
			float width(float);
			float width(void) const;

			float height(float);
			float height(void) const;

			float radius(float);
			float radius(void) const;

			vec3 position(vec3);
			vec3 position(void) const;

			vec3 direction(uint32_t, vec3);
			vec3 direction(uint32_t) const;

			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

		private:
			//vbos
			void vbo_fill_data(void) const;
			void vbo_stroke_data(void) const;
			void vbo_position_data(vertices::Model3D*) const;

			//ibos
			void ibo_fill_data(void) const;
			void ibo_stroke_data(void) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			float m_width;
			float m_height;
			float m_radius;
			vec3 m_position;
			vec3 m_directions[2];
			static uint32_t m_mesh;
		};
	}
}