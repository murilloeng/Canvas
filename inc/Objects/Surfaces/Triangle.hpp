#pragma once

//canvas
#include "inc/Math/vec3.hpp"
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
			vec3 point(unsigned) const;
			vec3 point(unsigned, const vec3&);

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex*) const;
			void vbo_stroke_data(vertices::Vertex*) const;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_points[3];
		};
	}
}