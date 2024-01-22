//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/1D/Arc.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Arc::Arc(void) : m_base{1, 0, 0}, m_center{0, 0, 0}, m_normal{0, 0, 1}, m_radius(0), m_angles{0, 0}
		{
			return;
		}

		//destructor
		Arc::~Arc(void)
		{
			return;
		}

		//data
		vec3 Arc::base(const vec3& base)
		{
			return m_base = base;
		}
		vec3 Arc::base(void) const
		{
			return m_base;
		}

		vec3 Arc::center(void) const
		{
			return m_center;
		}
		vec3 Arc::center(const vec3& center)
		{
			return m_center = center;
		}

		vec3 Arc::normal(void) const
		{
			return m_normal;
		}
		vec3 Arc::normal(const vec3& normal)
		{
			return m_normal = normal;
		}

		float Arc::radius(void) const
		{
			return m_radius;
		}
		float Arc::radius(float radius)
		{
			return m_radius = radius;
		}

		float Arc::angle(unsigned index) const
		{
			return m_angles[index];
		}
		float Arc::angle(unsigned index, float angle)
		{
			return m_angles[index] = angle;
		}

		//path
		vec3 Arc::path_hessian(float s) const
		{
			const vec3 t1 = m_base;
			const vec3 t2 = m_normal.cross(m_base);
			const float t = m_angles[0] + s * (m_angles[1] - m_angles[0]);
			return -m_radius * powf(m_angles[1] - m_angles[0], 2) * (sinf(t) * t2 + cosf(t) * t1);
		}
		vec3 Arc::path_position(float s) const
		{
			const vec3 t1 = m_base;
			const vec3 t2 = m_normal.cross(m_base);
			const float t = m_angles[0] + s * (m_angles[1] - m_angles[0]);
			return m_center + m_radius * (cosf(t) * t1 + sinf(t) * t2);
		}
		vec3 Arc::path_gradient(float s) const
		{
			const vec3 t1 = m_base;
			const vec3 t2 = m_normal.cross(m_base);
			const float t = m_angles[0] + s * (m_angles[1] - m_angles[0]);
			return m_radius * (m_angles[1] - m_angles[0]) * (cosf(t) * t2 - sinf(t) * t1);
		}
	}
}