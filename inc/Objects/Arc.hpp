#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Arc : public Object
		{
		public:
			//constructors
			Arc(void);

			//destructor
			~Arc(void);

			//data
			vec3 base(vec3);
			vec3 base(void) const;

			vec3 center(vec3);
			vec3 center(void) const;

			vec3 normal(vec3);
			vec3 normal(void) const;

			float radius(float);
			float radius(void) const;

			float angle(unsigned) const;
			float angle(unsigned, float);

			Color draw_color(Color);
			Color draw_color(void) const;

			Color fill_color(Color);
			Color fill_color(void) const;

			static unsigned mesh(void);
			static unsigned mesh(unsigned);

			//type
			objects::type type(void) const override;

		private:
			//misc
			unsigned current_mesh(void) const;

			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_base;
			vec3 m_center;
			vec3 m_normal;
			float m_radius;
			float m_angles[2];
			Color m_draw_color;
			Color m_fill_color;
			static unsigned m_mesh;
		};
	}
}