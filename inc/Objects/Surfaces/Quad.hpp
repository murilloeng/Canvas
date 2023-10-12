#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Quad : public Object
		{
		public:
			//constructors
			Quad(void);

			//destructor
			~Quad(void);

			//data
			vec3 point(unsigned) const;
			vec3 point(unsigned, const vec3&);

		private:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex*) const;
			void vbo_stroke_data(vertices::Vertex*) const;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_points[4];
		};
	}
}