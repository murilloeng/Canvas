#pragma once

//canvas
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

			static unsigned mesh(void);
			static unsigned mesh(unsigned);

			float* center(const float*);
			float* center(float, float, float);

			float* normal(const float*);
			float* normal(float, float, float);

			float* draw_color(const float*);
			float* draw_color(float, float, float);

			float* fill_color(const float*);
			float* fill_color(float, float, float);

			const float* center(void) const;
			const float* normal(void) const;
			const float* draw_color(void) const;
			const float* fill_color(void) const;

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
			float m_draw_color[3];
			float m_fill_color[3];
			static unsigned m_mesh;
		};
	}
}