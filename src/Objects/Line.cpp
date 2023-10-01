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

		vec3 Line::position(unsigned index) const
		{
			return m_positions[index];
		}
		vec3 Line::position(unsigned index, vec3 position)
		{
			return m_positions[index] = position;
		}

		//type
		objects::type Line::type(void) const
		{
			return objects::type::line;
		}

		//buffers
		unsigned Line::vbo_size(void) const
		{
			return 2 * m_draw;
		}
		unsigned Line::ibo_size(unsigned index) const
		{
			return (index == 1) * m_draw;
		}

		//draw
		void Line::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			if(!m_draw) return;
			for(unsigned i = 0; i < 2; i++)
			{
				ibo_data[1][m_ibo_index[1] + i] = m_vbo_index + i;
				((vertices::Model*) vbo_data + m_vbo_index + i)->m_color = m_colors[i];
				((vertices::Model*) vbo_data + m_vbo_index + i)->m_position = m_positions[i];
			}
		}
	}
}