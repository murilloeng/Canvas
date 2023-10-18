//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/1D/Line.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Line::Line(void) : m_points{{0, 0, 0}, {0, 0, 0}}
		{
			m_mesh = 1;
		}

		//destructor
		Line::~Line(void)
		{
			return;
		}

		//data
		vec3 Line::point(unsigned index) const
		{
			return m_points[index];
		}
		vec3 Line::point(unsigned index, const vec3& point)
		{
			return m_points[index] = point;
		}

		//path
		vec3 Line::path_hessian(float s) const
		{
			return {0, 0, 0};
		}
		vec3 Line::path_position(float s) const
		{
			return m_points[0] + s * (m_points[1] - m_points[0]);
		}
		vec3 Line::path_gradient(float s) const
		{
			return m_points[1] - m_points[0];
		}
	}
}