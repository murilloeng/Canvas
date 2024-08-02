//canvas
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

		//buffers
		uint32_t Triangle::vbo_size(uint32_t index) const
		{
			return 3 * (m_stroke + m_fill) * (index == 0);
		}
		uint32_t Triangle::ibo_size(uint32_t index) const
		{
			return 6 * (index == 1) * m_stroke + 3 * (index == 2) * m_fill;
		}

		//draw
		void Triangle::ibo_fill_data(uint32_t** ibo_data) const
		{
			ibo_data[2][m_ibo_index[2] + 0] = m_vbo_index[0] + 3 * m_stroke + 0;
			ibo_data[2][m_ibo_index[2] + 1] = m_vbo_index[0] + 3 * m_stroke + 2;
			ibo_data[2][m_ibo_index[2] + 2] = m_vbo_index[0] + 3 * m_stroke + 1;
			
		}
		void Triangle::ibo_stroke_data(uint32_t** ibo_data) const
		{
			ibo_data[1][m_ibo_index[1] + 0] = ibo_data[1][m_ibo_index[1] + 5] = m_vbo_index[0] + 0;
			ibo_data[1][m_ibo_index[1] + 1] = ibo_data[1][m_ibo_index[1] + 2] = m_vbo_index[0] + 1;
			ibo_data[1][m_ibo_index[1] + 3] = ibo_data[1][m_ibo_index[1] + 4] = m_vbo_index[0] + 2;
		}
		void Triangle::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model3D* vbo_fill_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0] + 3 * m_stroke;
			//vbo data
			for(uint32_t i = 0; i < 3; i++)
			{
				(vbo_fill_ptr + i)->m_color = m_color_fill;
				(vbo_fill_ptr + i)->m_position = m_points[i];
			}
		}
		void Triangle::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model3D* vbo_stroke_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			for(uint32_t i = 0; i < 3; i++)
			{
				(vbo_stroke_ptr + i)->m_color = m_color_stroke;
				(vbo_stroke_ptr + i)->m_position = m_points[i];
			}
		}
		void Triangle::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}