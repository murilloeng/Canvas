//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Curves/Line.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Line::Line(void) : m_points{{0, 0, 0}, {0, 0, 0}}
		{
			m_stroke_colors.resize(2);
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
		vec3 Line::hessian(float s) const
		{
			return {0, 0, 0};
		}
		vec3 Line::position(float s) const
		{
			return m_points[0] + s * (m_points[1] - m_points[0]);
		}
		vec3 Line::gradient(float s) const
		{
			return m_points[1] - m_points[0];
		}

		//type
		objects::type Line::type(void) const
		{
			return objects::type::line;
		}

		//buffers
		unsigned Line::vbo_size(void) const
		{
			return 2 * m_stroke;
		}
		unsigned Line::ibo_size(unsigned index) const
		{
			return (index == 1) * m_stroke;
		}

		//draw
		void Line::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			if(!m_stroke) return;
			for(unsigned i = 0; i < 2; i++)
			{
				ibo_data[1][m_ibo_index[1] + i] = m_vbo_index + i;
				((vertices::Model*) vbo_data + m_vbo_index + i)->m_position = m_points[i];
				((vertices::Model*) vbo_data + m_vbo_index + i)->m_color = m_stroke_colors[i];
			}
		}
	}
}