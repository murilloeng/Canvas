#pragma once

//std
#include <vector>

//Canvas
#include "Canvas/Canvas/inc/Objects/1D/Path.hpp"

namespace canvas
{
	namespace objects
	{
		class Bezier : public Path
		{
		public:
			//constructor
			Bezier(void);

			//destructor
			~Bezier(void);

			//types
			enum class Type : uint32_t {Conic, Cubic};

			//data
			Type type(Type);
			Type type(void) const;

			vec3 point(uint32_t, vec3);
			vec3 point(uint32_t) const;

			vec3 control(uint32_t, vec3);
			vec3 control(uint32_t) const;

			//path
			vec3 path_hessian(float) const override;
			vec3 path_position(float) const override;
			vec3 path_gradient(float) const override;

		private:
			//data
			Type m_type;
			vec3 m_points[2];
			vec3 m_controls[2];
		};
	}
}