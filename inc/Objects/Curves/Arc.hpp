#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Curves/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		class Arc : public Curve
		{
		public:
			//constructors
			Arc(void);

			//destructor
			~Arc(void);

			//data
			vec3 base(void) const;
			vec3 base(const vec3&);

			vec3 center(void) const;
			vec3 center(const vec3&);

			vec3 normal(void) const;
			vec3 normal(const vec3&);

			float radius(float);
			float radius(void) const;

			float angle(unsigned) const;
			float angle(unsigned, float);

			//path
			vec3 path_hessian(float) const override;
			vec3 path_position(float) const override;
			vec3 path_gradient(float) const override;

		private:
			//data
			vec3 m_base;
			vec3 m_center;
			vec3 m_normal;
			float m_radius;
			float m_angles[2];
		};
	}
}