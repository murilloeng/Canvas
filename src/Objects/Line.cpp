//std
#include <cstdio>
#include <cstdlib>
#include <cstring>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Line.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Line::Line(void) : 
			m_colors{{0, 0, 0}, {0, 0, 0}},
			m_positions{{0, 0, 0}, {0, 0, 0}}
		{
			return;
		}

		//destructor
		Line::~Line(void)
		{
			return;
		}

		//data
		const float* Line::color(unsigned index) const
		{
			return m_colors[index];
		}
		float* Line::color(unsigned index, const float* color)
		{
			return this->color(index, color[0], color[1], color[2]);
		}
		float* Line::color(unsigned index, float c1, float c2, float c3)
		{
			if(index == 2)
			{
				color(0, c1, c2, c3);
				color(1, c1, c2, c3);
				return nullptr;
			}
			else if(index < 2)
			{
				m_colors[index][0] = c1;
				m_colors[index][1] = c2;
				m_colors[index][2] = c3;
				return m_colors[index];
			}
			else
			{
				fprintf(stderr, "Error: Line color out of index!\n");
				exit(EXIT_FAILURE);
			}
		}

		const float* Line::position(unsigned index) const
		{
			return m_positions[index];
		}
		float* Line::position(unsigned index, const float* position)
		{
			return this->position(index, position[0], position[1], position[2]);
		}
		float* Line::position(unsigned index, float x1, float x2, float x3)
		{
			if(index < 2)
			{
				m_positions[index][0] = x1;
				m_positions[index][1] = x2;
				m_positions[index][2] = x3;
				return m_positions[index];
			}
			else
			{
				fprintf(stderr, "Error: Line position out of index!\n");
				exit(EXIT_FAILURE);
			}
		}

		//type
		objects::type Line::type(void) const
		{
			return objects::type::line;
		}

		//buffers
		unsigned Line::vbo_size(void) const
		{
			return 2;
		}
		unsigned Line::ibo_size(unsigned index) const
		{
			return index == 1 ? 1 : 0;
		}

		//draw
		void Line::draw(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			for(unsigned i = 0; i < 2; i++)
			{
				ibo_data[1][m_ibo_index[1] + i] = m_vbo_index + i;
				memcpy(((vertices::Model*) vbo_data + m_vbo_index + i)->m_color, m_colors[i], 3 * sizeof(float));
				memcpy(((vertices::Model*) vbo_data + m_vbo_index + i)->m_position, m_positions[i], 3 * sizeof(float));
			}
		}
	}
}