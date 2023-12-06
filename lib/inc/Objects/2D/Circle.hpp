#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Geometry.hpp"

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

			static unsigned mesh(void);
			static unsigned mesh(unsigned);

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
			vec3 m_center;
			vec3 m_normal;
			float m_radius;
			static unsigned m_mesh;
		};
	}
}