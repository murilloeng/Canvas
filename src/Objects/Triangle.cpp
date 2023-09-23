//std
#include <cstdio>
#include <cstdlib>
#include <cstring>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Triangle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Triangle::Triangle(void) : 
			m_draw(false), m_fill(false), 
			m_draw_color{0, 0, 0}, m_fill_color{0, 0, 0},
			m_positions{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
		{
			return;
		}

		//destructor
		Triangle::~Triangle(void)
		{
			return;
		}

		//data
		bool Triangle::draw(bool draw)
		{
			return m_draw = draw;
		}
		bool Triangle::draw(void) const
		{
			return m_draw;
		}

		bool Triangle::fill(bool fill)
		{
			return m_fill = fill;
		}
		bool Triangle::fill(void) const
		{
			return m_fill;
		}

		const float* Triangle::draw_color(void) const
		{
			return m_draw_color;
		}
		const float* Triangle::fill_color(void) const
		{
			return m_fill_color;
		}

		float* Triangle::draw_color(const float* draw_color)
		{
			return this->draw_color(draw_color[0], draw_color[1], draw_color[2]);
		}
		float* Triangle::draw_color(float c1, float c2, float c3)
		{
			m_draw_color[0] = c1;
			m_draw_color[1] = c2;
			m_draw_color[2] = c3;
			return m_draw_color;
		}

		float* Triangle::fill_color(const float* fill_color)
		{
			return this->fill_color(fill_color[0], fill_color[1], fill_color[2]);
		}
		float* Triangle::fill_color(float c1, float c2, float c3)
		{
			m_fill_color[0] = c1;
			m_fill_color[1] = c2;
			m_fill_color[2] = c3;
			return m_fill_color;
		}

		const float* Triangle::position(unsigned index) const
		{
			return m_positions[index];
		}
		float* Triangle::position(unsigned index, const float* position)
		{
			return this->position(index, position[0], position[1], position[2]);
		}
		float* Triangle::position(unsigned index, float x1, float x2, float x3)
		{
			if(index < 3)
			{
				m_positions[index][0] = x1;
				m_positions[index][1] = x2;
				m_positions[index][2] = x3;
				return m_positions[index];
			}
			else
			{
				fprintf(stderr, "Error: Triangle position out of index!\n");
				exit(EXIT_FAILURE);
			}
		}

		//type
		objects::type Triangle::type(void) const
		{
			return objects::type::triangle;
		}

		//buffers
		unsigned Triangle::vbo_size(void) const
		{
			return 3 * (m_draw + m_fill);
		}
		unsigned Triangle::ibo_size(unsigned index) const
		{
			return 3 * (index == 1) * m_draw + (index == 2) * m_fill;
		}

		//draw
		void Triangle::draw(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//data
			vertices::Model* vbo_draw_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + 3 * m_draw;
			//vbo data
			for(unsigned i = 0; i < 3; i++)
			{
				if(m_draw)
				{
					memcpy((vbo_draw_ptr + i)->m_color, m_draw_color, 3 * sizeof(float));
					memcpy((vbo_draw_ptr + i)->m_position, m_positions[i], 3 * sizeof(float));
				}
				if(m_fill)
				{
					memcpy((vbo_fill_ptr + i)->m_color, m_fill_color, 3 * sizeof(float));
					memcpy((vbo_fill_ptr + i)->m_position, m_positions[i], 3 * sizeof(float));
				}
			}
			//ibo data
			if(m_draw)
			{
				ibo_data[1][m_ibo_index[1] + 0] = ibo_data[1][m_ibo_index[1] + 5] = m_vbo_index + 0;
				ibo_data[1][m_ibo_index[1] + 1] = ibo_data[1][m_ibo_index[1] + 2] = m_vbo_index + 1;
				ibo_data[1][m_ibo_index[1] + 2] = ibo_data[1][m_ibo_index[1] + 4] = m_vbo_index + 2;
			}
			if(m_fill)
			{
				ibo_data[2][m_ibo_index[2] + 0] = m_vbo_index + 3 * m_draw + 0;
				ibo_data[2][m_ibo_index[2] + 1] = m_vbo_index + 3 * m_draw + 1;
				ibo_data[2][m_ibo_index[2] + 2] = m_vbo_index + 3 * m_draw + 2;
			}
		}
	}
}