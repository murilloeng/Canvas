//canvas
#include "Canvas/inc/Objects/0D/Point.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Point::Point(void) : m_position{0, 0, 0}
		{
			return;
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

		//buffers
		void Point::vbo_size(uint32_t vbo_counter[]) const
		{
			vbo_counter[0] += m_dot;
		}
		void Point::ibo_size(uint32_t ibo_counter[]) const
		{
			ibo_counter[0] += m_dot;
		}

		//draw
		void Point::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			//check
			if(!m_dot) return;
			//ibo data
			ibo_data[0][m_ibo_index[0]] = m_vbo_index[0];
			//vbo data
			((vertices::Model3D*) vbo_data[0] + m_vbo_index[0])->m_color = m_color_dot;
			((vertices::Model3D*) vbo_data[0] + m_vbo_index[0])->m_position = m_position;
		}
	}
}