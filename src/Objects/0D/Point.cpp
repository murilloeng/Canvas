//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/0D/Point.hpp"

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

		//draw
		void Point::buffers_size(void)
		{
			m_vbo_size[0] = m_dot;
			m_ibo_size[0] = m_dot;
		}
		void Point::buffers_data(void) const
		{
			//data
			if(!m_dot) return;
			uint32_t* ibo_ptr = ibo_data(0);
			vertices::Model3D* vbo_ptr = vbo_data_model_3D();
			//ibo data
			ibo_ptr[0] = m_vbo_index[0];
			//vbo data
			vbo_ptr->m_color = m_color_dot;
			vbo_ptr->m_position = m_position;
		}
	}
}