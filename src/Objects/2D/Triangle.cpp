//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/2D/Triangle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Triangle::Triangle(void) : m_points{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
		{
			return;
		}

		//destructor
		Triangle::~Triangle(void)
		{
			return;
		}

		vec3 Triangle::point(uint32_t index) const
		{
			return m_points[index];
		}
		vec3 Triangle::point(uint32_t index, const vec3& position)
		{
			return m_points[index] = position;
		}

		//data
		void Triangle::fill_data(void) const
		{
			//data
			uint32_t* ibo_ptr = m_scene->ibo_data(2) + m_ibo_index[2];
			vertices::Model3D* vbo_ptr = m_scene->vbo_data_model_3D() + m_vbo_index[0];
			//buffers
			for(uint32_t i = 0; i < 3; i++)
			{
				vbo_ptr[i + 3 * m_stroke].m_color = m_color_fill;
				vbo_ptr[i + 3 * m_stroke].m_position = m_points[i];
			}
			ibo_ptr[0] = m_vbo_index[0] + 3 * m_stroke + 0;
			ibo_ptr[1] = m_vbo_index[0] + 3 * m_stroke + 2;
			ibo_ptr[2] = m_vbo_index[0] + 3 * m_stroke + 1;
			
		}
		void Triangle::stroke_data(void) const
		{
			//data
			uint32_t* ibo_ptr = m_scene->ibo_data(1) + m_ibo_index[1];
			vertices::Model3D* vbo_ptr = m_scene->vbo_data_model_3D() + m_vbo_index[0];
			//vbo data
			for(uint32_t i = 0; i < 3; i++)
			{
				vbo_ptr[i].m_color = m_color_stroke;
				vbo_ptr[i].m_position = m_points[i];
			}
			ibo_ptr[0] = ibo_ptr[5] = m_vbo_index[0] + 0;
			ibo_ptr[1] = ibo_ptr[2] = m_vbo_index[0] + 1;
			ibo_ptr[3] = ibo_ptr[4] = m_vbo_index[0] + 2;
		}

		//buffers
		void Triangle::buffers_size(void)
		{
			m_ibo_size[2] = 3 * m_fill;
			m_ibo_size[1] = 6 * m_stroke;
			m_vbo_size[0] = 3 * (m_stroke + m_fill);
		}
		void Triangle::buffers_data(void) const
		{
			if(m_fill) fill_data();
			if(m_stroke) stroke_data();
		}
	}
}