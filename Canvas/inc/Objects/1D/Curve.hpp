#pragma once

//std
#include <cstdint>
#include <functional>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"

#include "Canvas/Canvas/inc/Objects/1D/Path.hpp"

namespace canvas
{
	namespace objects
	{
		class Curve : public Path
		{
		public:
			//constructors
			Curve(void);

			//destructor
			~Curve(void);

			//data
			float domain(uint32_t) const;
			float domain(uint32_t, float);

			std::function<vec3(float)> hessian(void) const;
			std::function<vec3(float)> gradient(void) const;
			std::function<vec3(float)> position(void) const;

			std::function<vec3(float)> hessian(std::function<vec3(float)>);
			std::function<vec3(float)> gradient(std::function<vec3(float)>);
			std::function<vec3(float)> position(std::function<vec3(float)>);

			//path
			vec3 path_hessian(float) const override;
			vec3 path_position(float) const override;
			vec3 path_gradient(float) const override;

		protected:
			//data
			float m_domain[2];
			std::function<vec3(float)> m_hessian;
			std::function<vec3(float)> m_gradient;
			std::function<vec3(float)> m_position;
		};
	}
}