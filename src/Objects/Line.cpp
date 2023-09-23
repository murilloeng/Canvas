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
		Line::Line(void) : m_colors{{0, 0, 0, 0}, {0, 0, 0, 0}}, m_positions{{0, 0, 0}, {0, 0, 0}}
		{
			return;
		}

		//destructor
		Line::~Line(void)
		{
			return;
		}

		//data
		Color Line::color(unsigned index) const
		{
			return m_colors[index];
		}
		Color Line::color(unsigned index, Color color)
		{
			if(index < 2)
			{
				return m_colors[index] = color;
			}
			else
			{
				this->color(0, color);
				this->color(1, color);
				return color;
			}
		}

		const float* Line::position(unsigned index) const
		{
			return m_positions[index];
		}
		const float* Line::position(unsigned index, const float* position)
		{
			return this->position(index, position[0], position[1], position[2]);
		}
		const float* Line::position(unsigned index, float x1, float x2, float x3)
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
				((vertices::Model*) vbo_data + m_vbo_index + i)->m_color = m_colors[i];
				memcpy(((vertices::Model*) vbo_data + m_vbo_index + i)->m_position, m_positions[i], 3 * sizeof(float));
			}
		}
	}
}