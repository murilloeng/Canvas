//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"
#include "inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Geometry::Geometry(void) : m_dot(true), m_fill(true), m_stroke(true)
		{
			return;
		}

		//destructor
		Geometry::~Geometry(void)
		{
			return;
		}

		//data
		bool Geometry::dot(bool dot)
		{
			return m_dot = dot;
		}
		bool Geometry::dot(void) const
		{
			return m_dot;
		}

		bool Geometry::fill(bool fill)
		{
			return m_fill = fill;
		}
		bool Geometry::fill(void) const
		{
			return m_fill;
		}

		bool Geometry::stroke(void) const
		{
			return m_stroke;
		}
		bool Geometry::stroke(bool stroke)
		{
			return m_stroke = stroke;
		}

		Color Geometry::color_dot(void) const
		{
			return m_color_dot;
		}
		Color Geometry::color_dot(const Color& color_dot)
		{
			return m_color_dot = color_dot;
		}

		Color Geometry::color_fill(void) const
		{
			return m_color_fill;
		}
		Color Geometry::color_fill(const Color& color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color Geometry::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color Geometry::color_stroke(const Color& color_stroke)
		{
			return m_color_stroke = color_stroke;
		}
	}
}