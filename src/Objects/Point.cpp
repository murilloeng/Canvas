//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Point.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Point::Point(void) : m_position{0, 0, 0}
		{
			m_dot_colors.resize(1);
		}

		//destructor
		Point::~Point(void)
		{
			return;
		}

		//data
		vec3 Point::position(void) const
		{
			return m_position;
		}
		vec3 Point::position(const vec3& position)
		{
			return m_position = position;
		}

		//type
		objects::type Point::type(void) const
		{
			return objects::type::point;
		}

		//buffers
		unsigned Point::vbo_size(void) const
		{
			return m_dot;
		}
		unsigned Point::ibo_size(unsigned index) const
		{
			return (index == 0) * m_dot;
		}

		//draw
		void Point::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//check
			if(!m_dot) return;
			//ibo data
			ibo_data[0][m_ibo_index[0]] = m_vbo_index;
			//vbo data
			((vertices::Model*) vbo_data + m_vbo_index)->m_position = m_position;
			((vertices::Model*) vbo_data + m_vbo_index)->m_color = m_dot_colors[0];
		}
	}
}