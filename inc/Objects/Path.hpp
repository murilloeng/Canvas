#pragma once

//std
#include <vector>

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Path : public Object
		{
		public:
			//constructors
			Path(void);

			//destructor
			~Path(void);

			//data
			void add_point(const vec3&);
			const std::vector<vec3>& points(void) const;

			//type
			objects::type type(void) const override;

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
			std::vector<vec3> m_points;
		};
	}
}