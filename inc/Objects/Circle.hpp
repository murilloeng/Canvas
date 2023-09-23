#pragma once

//canvas
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"
#include "inc/Kinematics/vec3.hpp"

namespace canvas
{
	namespace objects
	{
		class Circle : public Object
		{
		public:
			//constructors
			Circle(void);

			//destructor
			~Circle(void);

			//data
			bool draw(bool);
			bool draw(void) const;

			bool fill(bool);
			bool fill(void) const;

			vec3 center(vec3);
			vec3 center(void) const;

			vec3 normal(vec3);
			vec3 normal(void) const;

			float radius(float);
			float radius(void) const;

			Color draw_color(Color);
			Color draw_color(void) const;

			Color fill_color(Color);
			Color fill_color(void) const;

			static unsigned mesh(void);
			static unsigned mesh(unsigned);

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			bool m_draw;
			bool m_fill;
			vec3 m_center;
			vec3 m_normal;
			float m_radius;
			Color m_draw_color;
			Color m_fill_color;
			static unsigned m_mesh;
		};
	}
}