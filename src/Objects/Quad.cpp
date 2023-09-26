//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Quad.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Quad::Quad(void) : 
			m_positions{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
			m_draw_colors{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 
			m_fill_colors{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
		{
			return;
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

		Color Quad::draw_color(unsigned index) const
		{
			return m_draw_colors[index];
		}
		Color Quad::draw_color(unsigned index, Color draw_color)
		{
			if(index < 4)
			{
				return m_draw_colors[index] = draw_color;
			}
			else
			{
				this->draw_color(0, draw_color);
				this->draw_color(1, draw_color);
				this->draw_color(2, draw_color);
				this->draw_color(3, draw_color);
				return draw_color;
			}
		}

		Color Quad::fill_color(unsigned index) const
		{
			return m_fill_colors[index];
		}
		Color Quad::fill_color(unsigned index, Color fill_color)
		{
			if(index < 4)
			{
				return m_fill_colors[index] = fill_color;
			}
			else
			{
				this->fill_color(0, fill_color);
				this->fill_color(1, fill_color);
				this->fill_color(2, fill_color);
				this->fill_color(3, fill_color);
				return fill_color;
			}
		}

		//type
		objects::type Quad::type(void) const
		{
			return objects::type::quad;
		}

		//buffers
		unsigned Quad::vbo_size(void) const
		{
			return 4 * (m_draw + m_fill);
		}
		unsigned Quad::ibo_size(unsigned index) const
		{
			return 4 * (index == 1) * m_draw + 2 * (index == 2) * m_fill;
		}

		//draw
		void Quad::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//data
			vertices::Model* vbo_draw_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + 4 * m_draw;
			//vbo data
			for(unsigned i = 0; i < 4; i++)
			{
				if(m_draw)
				{
					(vbo_draw_ptr + i)->m_color = m_draw_colors[i];
					(vbo_draw_ptr + i)->m_position = m_positions[i];
				}
				if(m_fill)
				{
					(vbo_fill_ptr + i)->m_color = m_fill_colors[i];
					(vbo_fill_ptr + i)->m_position = m_positions[i];
				}
			}
			//ibo data
			if(m_draw)
			{
				ibo_data[1][m_ibo_index[1] + 0] = ibo_data[1][m_ibo_index[1] + 7] = m_vbo_index + 0;
				ibo_data[1][m_ibo_index[1] + 1] = ibo_data[1][m_ibo_index[1] + 2] = m_vbo_index + 1;
				ibo_data[1][m_ibo_index[1] + 3] = ibo_data[1][m_ibo_index[1] + 4] = m_vbo_index + 2;
				ibo_data[1][m_ibo_index[1] + 5] = ibo_data[1][m_ibo_index[1] + 6] = m_vbo_index + 3;
			}
			if(m_fill)
			{
				ibo_data[2][m_ibo_index[2] + 0] = m_vbo_index + 4 * m_draw + 0;
				ibo_data[2][m_ibo_index[2] + 1] = m_vbo_index + 4 * m_draw + 1;
				ibo_data[2][m_ibo_index[2] + 2] = m_vbo_index + 4 * m_draw + 2;
				ibo_data[2][m_ibo_index[2] + 3] = m_vbo_index + 4 * m_draw + 0;
				ibo_data[2][m_ibo_index[2] + 4] = m_vbo_index + 4 * m_draw + 2;
				ibo_data[2][m_ibo_index[2] + 5] = m_vbo_index + 4 * m_draw + 3;
			}
		}
	}
}