//Canvas
#include "Canvas/Canvas/inc/Objects/1D/Bezier.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Bezier::Bezier(void) : m_type{Type::Conic}
		{
			return;
		}

		//destructor
		Bezier::~Bezier(void)
		{
			return;
		}

		//data
		Bezier::Type Bezier::type(Type type)
		{
			return m_type = type;
		}
		Bezier::Type Bezier::type(void) const
		{
			return m_type;
		}

		vec3 Bezier::point(uint32_t index) const
		{
			return m_points[index];
		}
		vec3 Bezier::point(uint32_t index, vec3 point)
		{
			return m_points[index] = point;
		}

		vec3 Bezier::control(uint32_t index) const
		{
			return m_controls[index];
		}
		vec3 Bezier::control(uint32_t index, vec3 control)
		{
			return m_controls[index] = control;
		}

		//path
		vec3 Bezier::path_hessian(float t) const
		{
			const float s = 1 - t;
			if(m_type == Type::Conic)
			{
				return 2 * m_points[0] - 4 * m_controls[0] + 2 * m_points[1];
			}
			else
			{
				return 6 * s * m_points[0] + 6 * (t - 2 * s) * m_controls[0] + 6 * (s - 2 * t) * m_controls[1] + 6 * t * m_points[1];
			}
		}
		vec3 Bezier::path_position(float t) const
		{
			const float s = 1 - t;
			if(m_type == Type::Conic)
			{
				return s * s * m_points[0] + 2 * s * t * m_controls[0] + t * t * m_points[1];
			}
			else
			{
				return s * s * s * m_points[0] + 3 * s * s * t * m_controls[0] + 3 * s * t * t * m_controls[1] + t * t * t * m_points[1];
			}
		}
		vec3 Bezier::path_gradient(float t) const
		{
			const float s = 1 - t;
			if(m_type == Type::Conic)
			{
				return -2 * s * m_points[0] + 2 * (s - t) * m_controls[0] + 2 * t * m_points[1];
			}
			else
			{
				return -3 * s * s * m_points[0] - 3 * s * (2 * t - s) * m_controls[0] + 3 * t * (2 * s - t) * m_controls[1] + 3 * t * t * m_points[1];
			}
		}
	}
}
