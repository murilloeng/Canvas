//std
#include <cstdio>
#include <cstdlib>
#include <cstring>

//canvas
#include "inc/Vertices/Model.hpp"
#include "inc/Objects/Triangle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Triangle::Triangle(void) : 
			m_contour(false),
			m_colors{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
			m_positions{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
			m_contour_color{0, 0, 0}
		{
			return;
		}

		//destructor
		Triangle::~Triangle(void)
		{
			return;
		}

		//data
		bool Triangle::contour(void) const
		{
			return m_contour;
		}
		bool Triangle::contour(bool contour)
		{
			return m_contour = contour;
		}

		const float* Triangle::contour_color(void) const
		{
			return m_contour_color;
		}
		float* Triangle::contour_color(float c1, float c2, float c3)
		{
			m_contour_color[0] = c1;
			m_contour_color[1] = c2;
			m_contour_color[2] = c3;
			return m_contour_color;
		}

		const float* Triangle::color(unsigned index) const
		{
			return m_colors[index];
		}
		float* Triangle::color(unsigned index, const float* color)
		{
			return this->color(index, color[0], color[1], color[2]);
		}
		float* Triangle::color(unsigned index, float c1, float c2, float c3)
		{
			if(index == 3)
			{
				color(0, c1, c2, c3);
				color(1, c1, c2, c3);
				color(2, c1, c2, c3);
				return nullptr;
			}
			else if(index < 3)
			{
				m_colors[index][0] = c1;
				m_colors[index][1] = c2;
				m_colors[index][2] = c3;
				return m_colors[index];
			}
			else
			{
				fprintf(stderr, "Error: Triangle color out of index!\n");
				exit(EXIT_FAILURE);
			}
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

		//buffers
		unsigned Triangle::vbo_size(void) const
		{
			return m_contour ? 6 : 3;
		}
		unsigned Triangle::ibo_size(unsigned index) const
		{
			if(index == 0) return 0;
			if(index == 2) return 1;
			if(index == 1) return m_contour ? 3 : 0;
		}

		//draw
		void Triangle::draw(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			for(unsigned i = 0; i < 3; i++)
			{
				memcpy(((vertices::Model*) vbo_data + m_vbo_index + i)->m_color, m_colors[i], 3 * sizeof(float));
				memcpy(((vertices::Model*) vbo_data + m_vbo_index + i)->m_position, m_positions[i], 3 * sizeof(float));
				if(m_contour)
				{
					memcpy(((vertices::Model*) vbo_data + m_vbo_index + i + 3)->m_color, m_contour_color, 3 * sizeof(float));
					memcpy(((vertices::Model*) vbo_data + m_vbo_index + i + 3)->m_position, m_positions[i], 3 * sizeof(float));
				}
			}
			//ibo data
			ibo_data[2][m_ibo_index[2] + 0] = m_vbo_index + 0;
			ibo_data[2][m_ibo_index[2] + 1] = m_vbo_index + 1;
			ibo_data[2][m_ibo_index[2] + 2] = m_vbo_index + 2;
			//ibo data
			if(m_contour)
			{
				ibo_data[1][m_ibo_index[1] + 0] = ibo_data[1][m_ibo_index[1] + 5] = m_vbo_index + 3;
				ibo_data[1][m_ibo_index[1] + 1] = ibo_data[1][m_ibo_index[1] + 2] = m_vbo_index + 4;
				ibo_data[1][m_ibo_index[1] + 3] = ibo_data[1][m_ibo_index[1] + 4] = m_vbo_index + 5;
			}
		}
	}
}