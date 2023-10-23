#pragma once

//std
#include <vector>

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/1D/Path.hpp"

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
			vec3 point(unsigned) const;
			vec3 point(unsigned, const vec3&);

			vec3 control(unsigned, unsigned) const;
			vec3 control(unsigned, unsigned, const vec3&);

			void add_point(const vec3&);
			const std::vector<vec3>& points(void) const;
			const std::vector<vec3>& controls(void) const;

			//path
			float path_max(void) const override;
			vec3 path_hessian(float) const override;
			vec3 path_position(float) const override;
			vec3 path_gradient(float) const override;

		private:
			//data
			std::vector<vec3> m_points;
			std::vector<vec3> m_controls;
		};
	}
}