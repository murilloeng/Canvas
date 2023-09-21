//std
#include <cstring>

//canvas
#include "inc/Vertices/Model.hpp"
#include "inc/Objects/Triangle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Triangle::Triangle(void)
		{
			return;
		}

		//destructor
		Triangle::~Triangle(void)
		{
			return;
		}

		//buffers
		unsigned Triangle::vbo_size(void) const
		{
			return 3;
		}
		unsigned Triangle::ibo_size(unsigned index) const
		{
			return index == 2 ? 1 : 0;
		}

		//draw
		void Triangle::draw(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			for(unsigned i = 0; i < 3; i++)
			{
				memcpy(((vertices::Model*) vbo_data + m_vbo_index + i)->m_color, m_colors[i], 3 * sizeof(float));
				memcpy(((vertices::Model*) vbo_data + m_vbo_index + i)->m_position, m_positions[i], 3 * sizeof(float));
			}
			//ibo data
			ibo_data[2][m_ibo_index[2] + 0] = m_vbo_index + 0;
			ibo_data[2][m_ibo_index[2] + 1] = m_vbo_index + 1;
			ibo_data[2][m_ibo_index[2] + 2] = m_vbo_index + 2;
		}
	}
}