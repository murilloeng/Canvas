#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Curve : public Object
		{
		public:
			//constructors
			Curve(void);

			//destructor
			~Curve(void);

			//data
			unsigned mesh(unsigned);
			unsigned mesh(void) const;

			//path
			vec3 normal(float) const;
			vec3 tangent(float) const;
			vec3 binormal(float) const;
			virtual vec3 hessian(float) const = 0;
			virtual vec3 position(float) const = 0;
			virtual vec3 gradient(float) const = 0;

		protected:
			//data
			unsigned m_mesh;
		};
	}
}