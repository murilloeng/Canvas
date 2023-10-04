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
		class Spline : public Object
		{
		public:
			//constructors
			Spline(void);

			//destructor
			~Spline(void);

			//data
			static unsigned mesh(void);
			static unsigned mesh(unsigned);

			vec3 point(unsigned) const;
			vec3 point(unsigned, const vec3&);

			vec3 control(unsigned, unsigned) const;
			vec3 control(unsigned, unsigned, const vec3&);

			void add_point(const vec3&);
			const std::vector<vec3>& points(void) const;
			const std::vector<vec3>& controls(void) const;

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_stroke_data(unsigned**) const;
			void vbo_stroke_data(vertices::Vertex*) const;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			static unsigned m_mesh;
			std::vector<vec3> m_points;
			std::vector<vec3> m_controls;
		};
	}
}