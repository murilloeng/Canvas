#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Curves/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		class Line : public Curve
		{
		public:
			//constructors
			Line(void);

			//destructor
			~Line(void);

			//data
			vec3 point(unsigned) const;
			vec3 point(unsigned, const vec3&);

			//path
			vec3 path_hessian(float) const override;
			vec3 path_position(float) const override;
			vec3 path_gradient(float) const override;

		protected:
			//sizes
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//buffers
			void ibo_stroke_data(unsigned**) const override;
			void vbo_stroke_data(vertices::Vertex*) const override;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_points[2];
		};
	}
}