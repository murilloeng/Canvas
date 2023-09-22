#pragma once

//canvas
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Triangle : public Object
		{
		public:
			//constructors
			Triangle(void);

			//destructor
			~Triangle(void);

			//data
			bool contour(bool);
			bool contour(void) const;

			const float* contour_color(void) const;
			float* contour_color(const float*);
			float* contour_color(float, float, float);

			const float* color(unsigned) const;
			float* color(unsigned, const float*);
			float* color(unsigned, float, float, float);

			const float* position(unsigned) const;
			float* position(unsigned, const float*);
			float* position(unsigned, float, float, float);

			//type
			objects::type type(void) const override;

			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void draw(vertices::Vertex*, unsigned**) const override;

			//data
			bool m_contour;
			float m_colors[3][3];
			float m_positions[3][3];
			float m_contour_color[3];
		};
	}
}