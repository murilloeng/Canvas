#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Cylinder : public Object
		{
		public:
			//constructors
			Cylinder(void);

			//destructor
			~Cylinder(void);

			//data
			vec3 center(vec3);
			vec3 center(void) const;

			float radius(float);
			float radius(void) const;

			float height(float);
			float height(void) const;

			static unsigned mesh(void);
			static unsigned mesh(unsigned);

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_draw_data(unsigned**) const;
			void ibo_fill_data(unsigned**) const;
			void vbo_draw_data(vertices::Vertex*) const;
			void vbo_fill_data(vertices::Vertex*) const;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_center;
			float m_radius;
			float m_height;
			static unsigned m_mesh;
		};
	}
}