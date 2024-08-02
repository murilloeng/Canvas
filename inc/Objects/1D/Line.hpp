#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/1D/Path.hpp"

namespace canvas
{
	namespace objects
	{
		class Line : public Path
		{
		public:
			//constructors
			Line(void);

			//destructor
			~Line(void);

			//data
			vec3 point(uint32_t) const;
			vec3 point(uint32_t, const vec3&);

			//path
			vec3 path_hessian(float) const override;
			vec3 path_position(float) const override;
			vec3 path_gradient(float) const override;

		protected:
			//sizes
			uint32_t vbo_size(uint32_t) const override;
			uint32_t ibo_size(uint32_t) const override;

			//buffers
			void ibo_stroke_data(uint32_t**) const override;
			void vbo_stroke_data(vertices::Vertex**) const override;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			vec3 m_points[2];
		};
	}
}