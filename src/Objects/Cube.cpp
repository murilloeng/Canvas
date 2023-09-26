//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Cube.hpp"

//static data
static const float positions[] = {
	-1.0f, -1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	-1.0f, +1.0f, -1.0f,
	-1.0f, -1.0f, +1.0f,
	+1.0f, -1.0f, +1.0f,
	+1.0f, +1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f
};

namespace canvas
{
	namespace objects
	{
		//constructors
		Cube::Cube(void) : 
			m_draw(false), m_fill(false), 
			m_draw_colors{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 
			m_fill_colors{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
		{
			return;
		}

		//destructor
		Cube::~Cube(void)
		{
			return;
		}

		//data
		bool Cube::draw(bool draw)
		{
			return m_draw = draw;
		}
		bool Cube::draw(void) const
		{
			return m_draw;
		}

		bool Cube::fill(bool fill)
		{
			return m_fill = fill;
		}
		bool Cube::fill(void) const
		{
			return m_fill;
		}

		Color Cube::draw_color(unsigned index) const
		{
			return m_draw_colors[index];
		}
		Color Cube::draw_color(unsigned index, Color draw_color)
		{
			if(index < 8)
			{
				return m_draw_colors[index] = draw_color;
			}
			else
			{
				for(unsigned i = 0; i < 8; i++)
				{
					m_draw_colors[i] = draw_color;
				}
				return draw_color;
			}
		}

		Color Cube::fill_color(unsigned index) const
		{
			return m_fill_colors[index];
		}
		Color Cube::fill_color(unsigned index, Color fill_color)
		{
			if(index < 8)
			{
				return m_fill_colors[index] = fill_color;
			}
			else
			{
				for(unsigned i = 0; i < 8; i++)
				{
					m_fill_colors[i] = fill_color;
				}
				return fill_color;
			}
		}

		//type
		objects::type Cube::type(void) const
		{
			return objects::type::cube;
		}

		//buffers
		unsigned Cube::vbo_size(void) const
		{
			return 8 * (m_draw + m_fill);
		}
		unsigned Cube::ibo_size(unsigned index) const
		{
			return 12 * ((index == 1 && m_draw) + (index == 2 && m_fill));
		}

		//draw
		void Cube::ibo_draw_data(unsigned** ibo_data) const
		{
			//edges
			ibo_data[1][m_ibo_index[1] + 2 * 0 + 0] = m_vbo_index + 0;
			ibo_data[1][m_ibo_index[1] + 2 * 0 + 1] = m_vbo_index + 4;
			ibo_data[1][m_ibo_index[1] + 2 * 1 + 0] = m_vbo_index + 1;
			ibo_data[1][m_ibo_index[1] + 2 * 1 + 1] = m_vbo_index + 5;
			ibo_data[1][m_ibo_index[1] + 2 * 2 + 0] = m_vbo_index + 2;
			ibo_data[1][m_ibo_index[1] + 2 * 2 + 1] = m_vbo_index + 6;
			ibo_data[1][m_ibo_index[1] + 2 * 3 + 0] = m_vbo_index + 3;
			ibo_data[1][m_ibo_index[1] + 2 * 3 + 1] = m_vbo_index + 7;
			//face -x3
			ibo_data[1][m_ibo_index[1] + 2 * 4 + 0] = ibo_data[1][m_ibo_index[1] + 2 * 7 + 1] = m_vbo_index + 0;
			ibo_data[1][m_ibo_index[1] + 2 * 4 + 1] = ibo_data[1][m_ibo_index[1] + 2 * 5 + 0] = m_vbo_index + 1;
			ibo_data[1][m_ibo_index[1] + 2 * 5 + 1] = ibo_data[1][m_ibo_index[1] + 2 * 6 + 0] = m_vbo_index + 2;
			ibo_data[1][m_ibo_index[1] + 2 * 6 + 1] = ibo_data[1][m_ibo_index[1] + 2 * 7 + 0] = m_vbo_index + 3;
			//face +x3
			ibo_data[1][m_ibo_index[1] + 2 *  8 + 0] = ibo_data[1][m_ibo_index[1] + 2 * 11 + 1] = m_vbo_index + 4;
			ibo_data[1][m_ibo_index[1] + 2 *  8 + 1] = ibo_data[1][m_ibo_index[1] + 2 *  9 + 0] = m_vbo_index + 5;
			ibo_data[1][m_ibo_index[1] + 2 *  9 + 1] = ibo_data[1][m_ibo_index[1] + 2 * 10 + 0] = m_vbo_index + 6;
			ibo_data[1][m_ibo_index[1] + 2 * 10 + 1] = ibo_data[1][m_ibo_index[1] + 2 * 11 + 0] = m_vbo_index + 7;
		}
		void Cube::ibo_fill_data(unsigned** ibo_data) const
		{
			//face -x3
			ibo_data[2][m_ibo_index[2] + 3 * 0 + 2] = m_vbo_index + 8 * m_draw + 1;
			ibo_data[2][m_ibo_index[2] + 3 * 1 + 1] = m_vbo_index + 8 * m_draw + 3;
			ibo_data[2][m_ibo_index[2] + 3 * 0 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 1 + 0] = m_vbo_index + 8 * m_draw + 0;
			ibo_data[2][m_ibo_index[2] + 3 * 0 + 1] = ibo_data[2][m_ibo_index[2] + 3 * 1 + 2] = m_vbo_index + 8 * m_draw + 2;
			//face +x3
			ibo_data[2][m_ibo_index[2] + 3 * 2 + 1] = m_vbo_index + 8 * m_draw + 5;
			ibo_data[2][m_ibo_index[2] + 3 * 3 + 2] = m_vbo_index + 8 * m_draw + 7;
			ibo_data[2][m_ibo_index[2] + 3 * 2 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 3 + 0] = m_vbo_index + 8 * m_draw + 4;
			ibo_data[2][m_ibo_index[2] + 3 * 2 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 3 + 1] = m_vbo_index + 8 * m_draw + 6;
			//face -x2
			ibo_data[2][m_ibo_index[2] + 3 * 4 + 1] = m_vbo_index + 8 * m_draw + 1;
			ibo_data[2][m_ibo_index[2] + 3 * 5 + 2] = m_vbo_index + 8 * m_draw + 4;
			ibo_data[2][m_ibo_index[2] + 3 * 4 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 5 + 0] = m_vbo_index + 8 * m_draw + 0;
			ibo_data[2][m_ibo_index[2] + 3 * 4 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 5 + 1] = m_vbo_index + 8 * m_draw + 5;
			//face +x1
			ibo_data[2][m_ibo_index[2] + 3 * 6 + 1] = m_vbo_index + 8 * m_draw + 2;
			ibo_data[2][m_ibo_index[2] + 3 * 7 + 2] = m_vbo_index + 8 * m_draw + 5;
			ibo_data[2][m_ibo_index[2] + 3 * 6 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 7 + 0] = m_vbo_index + 8 * m_draw + 1;
			ibo_data[2][m_ibo_index[2] + 3 * 6 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 7 + 1] = m_vbo_index + 8 * m_draw + 6;
			//face +x2
			ibo_data[2][m_ibo_index[2] + 3 * 8 + 1] = m_vbo_index + 8 * m_draw + 3;
			ibo_data[2][m_ibo_index[2] + 3 * 9 + 2] = m_vbo_index + 8 * m_draw + 6;
			ibo_data[2][m_ibo_index[2] + 3 * 8 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 9 + 0] = m_vbo_index + 8 * m_draw + 2;
			ibo_data[2][m_ibo_index[2] + 3 * 8 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 9 + 1] = m_vbo_index + 8 * m_draw + 7;
			//face -x3
			ibo_data[2][m_ibo_index[2] + 3 * 10 + 1] = m_vbo_index + 8 * m_draw + 0;
			ibo_data[2][m_ibo_index[2] + 3 * 11 + 2] = m_vbo_index + 8 * m_draw + 7;
			ibo_data[2][m_ibo_index[2] + 3 * 10 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 11 + 0] = m_vbo_index + 8 * m_draw + 3;
			ibo_data[2][m_ibo_index[2] + 3 * 10 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 11 + 1] = m_vbo_index + 8 * m_draw + 4;
		}
		void Cube::draw(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			vertices::Model* vbo_draw_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + 8 * m_draw;
			//vbo data
			for(unsigned i = 0; i < 8; i++)
			{
				if(m_draw)
				{
					(vbo_draw_ptr + i)->m_color = m_draw_colors[i];
					(vbo_draw_ptr + i)->m_position = positions + 3 * i;
				}
				if(m_fill)
				{
					(vbo_fill_ptr + i)->m_color = m_fill_colors[i];
					(vbo_fill_ptr + i)->m_position = positions + 3 * i;
				}
			}
			//ibo data
			if(m_draw) ibo_draw_data(ibo_data);
			if(m_fill) ibo_fill_data(ibo_data);
		}
	}
}