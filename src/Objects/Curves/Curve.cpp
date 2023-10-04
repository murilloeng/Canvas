//std
#include <cmath>

//canvas
#include "inc/Objects/Curves/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Curve::Curve(void) : m_mesh(40)
		{
			return;
		}

		//destructor
		Curve::~Curve(void)
		{
			return;
		}

		//data
		unsigned Curve::mesh(void) const
		{
			return m_mesh;
		}
		unsigned Curve::mesh(unsigned mesh)
		{
			return m_mesh = mesh;
		}

		//path
		vec3 Curve::normal(float s) const
		{
			//path
			const vec3 h = hessian(s);
			const vec3 g = gradient(s);
			//normal
			const vec3 t = g.unit();
			return (h - h.inner(t) * t).unit();
		}
		vec3 Curve::tangent(float s) const
		{
			return gradient(s).unit();
		}
		vec3 Curve::binormal(float s) const
		{
			return tangent(s).cross(normal(s));
		}
	}
}