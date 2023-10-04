//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Triangle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Triangle::Triangle(void) : m_positions{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
		{
			m_fill_colors.resize(3);
			m_stroke_colors.resize(3);
		}

		//destructor
		Triangle::~Triangle(void)
		{
			return;
		}

		vec3 Triangle::position(unsigned index) const
		{
			return m_positions[index];
		}
		vec3 Triangle::position(unsigned index, const vec3& position)
		{
			return m_positions[index] = position;
		}

		//type
		objects::type Triangle::type(void) const
		{
			return objects::type::triangle;
		}

		//buffers
		unsigned Triangle::vbo_size(void) const
		{
			return 3 * (m_stroke + m_fill);
		}
		unsigned Triangle::ibo_size(unsigned index) const
		{
			return 3 * (index == 1) * m_stroke + (index == 2) * m_fill;
		}

		//draw
		void Triangle::ibo_fill_data(unsigned** ibo_data) const
		{
			ibo_data[2][m_ibo_index[2] + 0] = m_vbo_index + 3 * m_stroke + 0;
			ibo_data[2][m_ibo_index[2] + 1] = m_vbo_index + 3 * m_stroke + 1;
			ibo_data[2][m_ibo_index[2] + 2] = m_vbo_index + 3 * m_stroke + 2;
			
		}
		void Triangle::ibo_stroke_data(unsigned** ibo_data) const
		{
			ibo_data[1][m_ibo_index[1] + 0] = ibo_data[1][m_ibo_index[1] + 5] = m_vbo_index + 0;
			ibo_data[1][m_ibo_index[1] + 1] = ibo_data[1][m_ibo_index[1] + 2] = m_vbo_index + 1;
			ibo_data[1][m_ibo_index[1] + 3] = ibo_data[1][m_ibo_index[1] + 4] = m_vbo_index + 2;
		}
		void Triangle::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + 3 * m_stroke;
			//vbo data
			for(unsigned i = 0; i < 3; i++)
			{
				(vbo_fill_ptr + i)->m_color = m_fill_colors[i];
				(vbo_fill_ptr + i)->m_position = m_positions[i];
			}
		}
		void Triangle::vbo_stroke_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_stroke_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//vbo data
			for(unsigned i = 0; i < 3; i++)
			{
				(vbo_stroke_ptr + i)->m_color = m_stroke_colors[i];
				(vbo_stroke_ptr + i)->m_position = m_positions[i];
			}
		}
		void Triangle::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			//ibo data
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}