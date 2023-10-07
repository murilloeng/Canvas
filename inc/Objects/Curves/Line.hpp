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

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_points[2];
		};
	}
}