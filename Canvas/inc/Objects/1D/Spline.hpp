#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"

#include "Canvas/Canvas/inc/Objects/1D/Path.hpp"

namespace canvas
{
	namespace objects
	{
		class Spline : public Path
		{
		public:
			//constructors
			Spline(void);

			//destructor
			~Spline(void);

			//data
			vec3 point(uint32_t) const;
			vec3 point(uint32_t, const vec3&);

			vec3 control(uint32_t, uint32_t) const;
			vec3 control(uint32_t, uint32_t, const vec3&);

			void add_point(const vec3&);
			const std::vector<vec3>& points(void) const;
			const std::vector<vec3>& controls(void) const;

			//path
			float path_max(void) const override;
			vec3 path_hessian(float) const override;
			vec3 path_position(float) const override;
			vec3 path_gradient(float) const override;

		protected:
			//data
			std::vector<vec3> m_points;
			std::vector<vec3> m_controls;
		};
	}
}