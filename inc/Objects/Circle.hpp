#pragma once

//canvas
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

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

			float radius(float);
			float radius(void) const;

			Color draw_color(Color);
			Color draw_color(void) const;

			Color fill_color(Color);
			Color fill_color(void) const;

			static unsigned mesh(void);
			static unsigned mesh(unsigned);

			const float* center(void) const;
			const float* center(const float*);
			const float* center(float, float, float);

			const float* normal(void) const;
			const float* normal(const float*);
			const float* normal(float, float, float);

			//type
			objects::type type(void) const override;

			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			bool m_draw;
			bool m_fill;
			float m_radius;
			float m_center[3];
			float m_normal[3];
			Color m_draw_color;
			Color m_fill_color;
			static unsigned m_mesh;
		};
	}
}