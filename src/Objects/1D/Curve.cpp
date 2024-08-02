//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"

#include "Canvas/inc/Objects/1D/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Curve::Curve(void) : m_domain{0, 1}
		{
			return;
		}

		//destructor
		Curve::~Curve(void)
		{
			return;
		}

		//data
		float Curve::domain(unsigned index) const
		{
			return m_domain[index];
		}
		float Curve::domain(unsigned index, float domain)
		{
			return m_domain[index] = domain;
		}

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
			const float a = m_domain[0];
			const float b = m_domain[1];
			return m_hessian(a + (b - a) * s);
		}
		vec3 Curve::path_position(float s) const
		{
			const float a = m_domain[0];
			const float b = m_domain[1];
			return m_position(a + (b - a) * s);
		}
		vec3 Curve::path_gradient(float s) const
		{
			const float a = m_domain[0];
			const float b = m_domain[1];
			return m_gradient(a + (b - a) * s);
		}
	}
}