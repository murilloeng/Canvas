//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"

#include "Canvas/inc/Objects/2D/Quad.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Quad::Quad(void) : m_points{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
		{
			return;
		}

		//destructor
		Quad::~Quad(void)
		{
			return;
		}

		//data
		vec3 Quad::point(unsigned index) const
		{
			return m_points[index];
		}
		vec3 Quad::point(unsigned index, const vec3& position)
		{
			return m_points[index] = position;
		}

		//buffers
		unsigned Quad::vbo_size(unsigned index) const
		{
			return 4 * (m_stroke + m_fill) * (index == 0);
		}
		unsigned Quad::ibo_size(unsigned index) const
		{
			return 4 * (index == 1) * m_stroke + 2 * (index == 2) * m_fill;
		}

		//draw
		void Quad::ibo_fill_data(unsigned** ibo_data) const
		{
			ibo_data[2][m_ibo_index[2] + 0] = m_vbo_index[0] + 4 * m_stroke + 0;
			ibo_data[2][m_ibo_index[2] + 1] = m_vbo_index[0] + 4 * m_stroke + 2;
			ibo_data[2][m_ibo_index[2] + 2] = m_vbo_index[0] + 4 * m_stroke + 1;
			ibo_data[2][m_ibo_index[2] + 3] = m_vbo_index[0] + 4 * m_stroke + 0;
			ibo_data[2][m_ibo_index[2] + 4] = m_vbo_index[0] + 4 * m_stroke + 3;
			ibo_data[2][m_ibo_index[2] + 5] = m_vbo_index[0] + 4 * m_stroke + 2;
		}
		void Quad::ibo_stroke_data(unsigned** ibo_data) const
		{
			ibo_data[1][m_ibo_index[1] + 0] = ibo_data[1][m_ibo_index[1] + 7] = m_vbo_index[0] + 0;
			ibo_data[1][m_ibo_index[1] + 1] = ibo_data[1][m_ibo_index[1] + 2] = m_vbo_index[0] + 1;
			ibo_data[1][m_ibo_index[1] + 3] = ibo_data[1][m_ibo_index[1] + 4] = m_vbo_index[0] + 2;
			ibo_data[1][m_ibo_index[1] + 5] = ibo_data[1][m_ibo_index[1] + 6] = m_vbo_index[0] + 3;
		}
		void Quad::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model3D* vbo_fill_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0] + 4 * m_stroke;
			//vbo data
			for(unsigned i = 0; i < 4; i++)
			{
				(vbo_fill_ptr + i)->m_color = m_color_fill;
				(vbo_fill_ptr + i)->m_position = m_points[i];
			}
		}
		void Quad::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model3D* vbo_stroke_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			for(unsigned i = 0; i < 4; i++)
			{
				(vbo_stroke_ptr + i)->m_color = m_color_stroke;
				(vbo_stroke_ptr + i)->m_position = m_points[i];
			}
		}
		void Quad::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}