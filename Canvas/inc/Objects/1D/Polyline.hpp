#pragma once

//std
#include <vector>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Path.hpp"

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
			std::vector<vec3>& vertices(void);
			const std::vector<vec3>& vertices(void) const;

		protected:
			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			std::vector<vec3> m_vertices;
		};
	}
}