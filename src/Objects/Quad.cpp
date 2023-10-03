//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Quad.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Quad::Quad(void) : m_positions{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
		{
			m_fill_colors.resize(4);
			m_stroke_colors.resize(4);
		}

		//destructor
		Quad::~Quad(void)
		{
			return;
		}

		//data
		vec3 Quad::position(unsigned index) const
		{
			return m_positions[index];
		}
		vec3 Quad::position(unsigned index, vec3 position)
		{
			return m_positions[index] = position;
		}

		//type
		objects::type Quad::type(void) const
		{
			return objects::type::quad;
		}

		//buffers
		unsigned Quad::vbo_size(void) const
		{
			return 4 * (m_stroke + m_fill);
		}
		unsigned Quad::ibo_size(unsigned index) const
		{
			return 4 * (index == 1) * m_stroke + 2 * (index == 2) * m_fill;
		}

		//draw
		void Quad::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//data
			vertices::Model* vbo_draw_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + 4 * m_stroke;
			//vbo data
			for(unsigned i = 0; i < 4; i++)
			{
				if(m_stroke)
				{
					(vbo_draw_ptr + i)->m_color = m_stroke_colors[i];
					(vbo_draw_ptr + i)->m_position = m_positions[i];
				}
				if(m_fill)
				{
					(vbo_fill_ptr + i)->m_color = m_fill_colors[i];
					(vbo_fill_ptr + i)->m_position = m_positions[i];
				}
			}
			//ibo data
			if(m_stroke)
			{
				ibo_data[1][m_ibo_index[1] + 0] = ibo_data[1][m_ibo_index[1] + 7] = m_vbo_index + 0;
				ibo_data[1][m_ibo_index[1] + 1] = ibo_data[1][m_ibo_index[1] + 2] = m_vbo_index + 1;
				ibo_data[1][m_ibo_index[1] + 3] = ibo_data[1][m_ibo_index[1] + 4] = m_vbo_index + 2;
				ibo_data[1][m_ibo_index[1] + 5] = ibo_data[1][m_ibo_index[1] + 6] = m_vbo_index + 3;
			}
			if(m_fill)
			{
				ibo_data[2][m_ibo_index[2] + 0] = m_vbo_index + 4 * m_stroke + 0;
				ibo_data[2][m_ibo_index[2] + 1] = m_vbo_index + 4 * m_stroke + 1;
				ibo_data[2][m_ibo_index[2] + 2] = m_vbo_index + 4 * m_stroke + 2;
				ibo_data[2][m_ibo_index[2] + 3] = m_vbo_index + 4 * m_stroke + 0;
				ibo_data[2][m_ibo_index[2] + 4] = m_vbo_index + 4 * m_stroke + 2;
				ibo_data[2][m_ibo_index[2] + 5] = m_vbo_index + 4 * m_stroke + 3;
			}
		}
	}
}