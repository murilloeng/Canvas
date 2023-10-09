//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Volumes/Cube.hpp"

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
		Cube::Cube(void) : m_sizes{1.0f, 1.0f, 1.0f}, m_center{0.0f, 0.0f, 0.0f}
		{
			return;
		}

		//destructor
		Cube::~Cube(void)
		{
			return;
		}

		//data
		vec3 Cube::sizes(const vec3& sizes)
		{
			return m_sizes = sizes;
		}
		vec3 Cube::sizes(void) const
		{
			return m_sizes;
		}

		vec3 Cube::center(const vec3& center)
		{
			return m_center = center;
		}
		vec3 Cube::center(void) const
		{
			return m_center;
		}

		//buffers
		unsigned Cube::vbo_size(void) const
		{
			return 8 * (m_stroke + m_fill);
		}
		unsigned Cube::ibo_size(unsigned index) const
		{
			return 12 * ((index == 1 && m_stroke) + (index == 2 && m_fill));
		}

		//draw
		void Cube::ibo_stroke_data(unsigned** ibo_data) const
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
			ibo_data[2][m_ibo_index[2] + 3 * 0 + 2] = m_vbo_index + 8 * m_stroke + 1;
			ibo_data[2][m_ibo_index[2] + 3 * 1 + 1] = m_vbo_index + 8 * m_stroke + 3;
			ibo_data[2][m_ibo_index[2] + 3 * 0 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 1 + 0] = m_vbo_index + 8 * m_stroke + 0;
			ibo_data[2][m_ibo_index[2] + 3 * 0 + 1] = ibo_data[2][m_ibo_index[2] + 3 * 1 + 2] = m_vbo_index + 8 * m_stroke + 2;
			//face +x3
			ibo_data[2][m_ibo_index[2] + 3 * 2 + 1] = m_vbo_index + 8 * m_stroke + 5;
			ibo_data[2][m_ibo_index[2] + 3 * 3 + 2] = m_vbo_index + 8 * m_stroke + 7;
			ibo_data[2][m_ibo_index[2] + 3 * 2 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 3 + 0] = m_vbo_index + 8 * m_stroke + 4;
			ibo_data[2][m_ibo_index[2] + 3 * 2 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 3 + 1] = m_vbo_index + 8 * m_stroke + 6;
			//face -x2
			ibo_data[2][m_ibo_index[2] + 3 * 4 + 1] = m_vbo_index + 8 * m_stroke + 1;
			ibo_data[2][m_ibo_index[2] + 3 * 5 + 2] = m_vbo_index + 8 * m_stroke + 4;
			ibo_data[2][m_ibo_index[2] + 3 * 4 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 5 + 0] = m_vbo_index + 8 * m_stroke + 0;
			ibo_data[2][m_ibo_index[2] + 3 * 4 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 5 + 1] = m_vbo_index + 8 * m_stroke + 5;
			//face +x1
			ibo_data[2][m_ibo_index[2] + 3 * 6 + 1] = m_vbo_index + 8 * m_stroke + 2;
			ibo_data[2][m_ibo_index[2] + 3 * 7 + 2] = m_vbo_index + 8 * m_stroke + 5;
			ibo_data[2][m_ibo_index[2] + 3 * 6 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 7 + 0] = m_vbo_index + 8 * m_stroke + 1;
			ibo_data[2][m_ibo_index[2] + 3 * 6 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 7 + 1] = m_vbo_index + 8 * m_stroke + 6;
			//face +x2
			ibo_data[2][m_ibo_index[2] + 3 * 8 + 1] = m_vbo_index + 8 * m_stroke + 3;
			ibo_data[2][m_ibo_index[2] + 3 * 9 + 2] = m_vbo_index + 8 * m_stroke + 6;
			ibo_data[2][m_ibo_index[2] + 3 * 8 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 9 + 0] = m_vbo_index + 8 * m_stroke + 2;
			ibo_data[2][m_ibo_index[2] + 3 * 8 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 9 + 1] = m_vbo_index + 8 * m_stroke + 7;
			//face -x3
			ibo_data[2][m_ibo_index[2] + 3 * 10 + 1] = m_vbo_index + 8 * m_stroke + 0;
			ibo_data[2][m_ibo_index[2] + 3 * 11 + 2] = m_vbo_index + 8 * m_stroke + 7;
			ibo_data[2][m_ibo_index[2] + 3 * 10 + 0] = ibo_data[2][m_ibo_index[2] + 3 * 11 + 0] = m_vbo_index + 8 * m_stroke + 3;
			ibo_data[2][m_ibo_index[2] + 3 * 10 + 2] = ibo_data[2][m_ibo_index[2] + 3 * 11 + 1] = m_vbo_index + 8 * m_stroke + 4;
		}
		void Cube::vbo_stroke_data(vertices::Vertex* vbo_data) const
		{
			//data
			const mat4 A = mat4::scaling(m_sizes / 2);
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//vbo data
			for(unsigned i = 0; i < 8; i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = m_center + A * vec3(positions + 3 * i);
			}
		}
		void Cube::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			//data
			const mat4 A = mat4::scaling(m_sizes / 2);
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index + 8 * m_stroke;
			//vbo data
			for(unsigned i = 0; i < 8; i++)
			{
				(vbo_ptr + i)->m_color = m_color_fill;
				(vbo_ptr + i)->m_position = m_center + A * vec3(positions + 3 * i);
			}
		}
		void Cube::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
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