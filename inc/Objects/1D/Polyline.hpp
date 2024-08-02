#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/1D/Path.hpp"

namespace canvas
{
	namespace objects
	{
		class Polyline : public Path
		{
		public:
			//constructors
			Polyline(void);

			//destructor
			~Polyline(void);

			//path
			float path_max(void) const override;
			vec3 path_hessian(float) const override;
			vec3 path_position(float) const override;
			vec3 path_gradient(float) const override;

			//data
			std::vector<vec3>& points(void);
			const std::vector<vec3>& points(void) const;

		protected:
			//buffers
			uint32_t vbo_size(uint32_t) const override;
			uint32_t ibo_size(uint32_t) const override;

			//draw
			void ibo_stroke_data(uint32_t**) const override;
			void vbo_stroke_data(vertices::Vertex**) const override;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			std::vector<vec3> m_points;
		};
	}
}