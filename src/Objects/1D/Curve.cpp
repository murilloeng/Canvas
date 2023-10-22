//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/1D/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Curve::Curve(void)
		{
			return;
		}

		//destructor
		Curve::~Curve(void)
		{
			return;
		}

		//data
		std::function<vec3(float)> Curve::hessian(void) const
		{
			return m_hessian;
		}
		std::function<vec3(float)> Curve::gradient(void) const
		{
			return m_gradient;
		}
		std::function<vec3(float)> Curve::position(void) const
		{
			return m_position;
		}

		std::function<vec3(float)> Curve::hessian(std::function<vec3(float)> hessian)
		{
			return m_hessian = hessian;
		}
		std::function<vec3(float)> Curve::gradient(std::function<vec3(float)> gradient)
		{
			return m_gradient = gradient;
		}
		std::function<vec3(float)> Curve::position(std::function<vec3(float)> position)
		{
			return m_position = position;
		}

		//path
		vec3 Curve::path_hessian(float s) const
		{
			return m_hessian(s);
		}
		vec3 Curve::path_position(float s) const
		{
			return m_position(s);
		}
		vec3 Curve::path_gradient(float s) const
		{
			return m_gradient(s);
		}
	}
}