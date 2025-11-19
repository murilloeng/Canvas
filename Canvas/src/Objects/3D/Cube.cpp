//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Cube.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"

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
		Cube::Cube(void)
		{
			return;
		}

		//destructor
		Cube::~Cube(void)
		{
			return;
		}

		//data
		void Cube::ibo_stroke_data(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(1);
			//edges
			ibo_ptr[2 * 0 + 0] = m_vbo_index[0] + 0;
			ibo_ptr[2 * 0 + 1] = m_vbo_index[0] + 4;
			ibo_ptr[2 * 1 + 0] = m_vbo_index[0] + 1;
			ibo_ptr[2 * 1 + 1] = m_vbo_index[0] + 5;
			ibo_ptr[2 * 2 + 0] = m_vbo_index[0] + 2;
			ibo_ptr[2 * 2 + 1] = m_vbo_index[0] + 6;
			ibo_ptr[2 * 3 + 0] = m_vbo_index[0] + 3;
			ibo_ptr[2 * 3 + 1] = m_vbo_index[0] + 7;
			//face -x3
			ibo_ptr[2 * 4 + 0] = ibo_ptr[2 * 7 + 1] = m_vbo_index[0] + 0;
			ibo_ptr[2 * 4 + 1] = ibo_ptr[2 * 5 + 0] = m_vbo_index[0] + 1;
			ibo_ptr[2 * 5 + 1] = ibo_ptr[2 * 6 + 0] = m_vbo_index[0] + 2;
			ibo_ptr[2 * 6 + 1] = ibo_ptr[2 * 7 + 0] = m_vbo_index[0] + 3;
			//face +x3
			ibo_ptr[2 *  8 + 0] = ibo_ptr[2 * 11 + 1] = m_vbo_index[0] + 4;
			ibo_ptr[2 *  8 + 1] = ibo_ptr[2 *  9 + 0] = m_vbo_index[0] + 5;
			ibo_ptr[2 *  9 + 1] = ibo_ptr[2 * 10 + 0] = m_vbo_index[0] + 6;
			ibo_ptr[2 * 10 + 1] = ibo_ptr[2 * 11 + 0] = m_vbo_index[0] + 7;
		}
		void Cube::ibo_fill_data(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(2);
			//face -x3
			ibo_ptr[3 * 0 + 2] = m_vbo_index[0] + 8 * m_stroke + 1;
			ibo_ptr[3 * 1 + 1] = m_vbo_index[0] + 8 * m_stroke + 3;
			ibo_ptr[3 * 0 + 0] = ibo_ptr[3 * 1 + 0] = m_vbo_index[0] + 8 * m_stroke + 0;
			ibo_ptr[3 * 0 + 1] = ibo_ptr[3 * 1 + 2] = m_vbo_index[0] + 8 * m_stroke + 2;
			//face +x3
			ibo_ptr[3 * 2 + 1] = m_vbo_index[0] + 8 * m_stroke + 5;
			ibo_ptr[3 * 3 + 2] = m_vbo_index[0] + 8 * m_stroke + 7;
			ibo_ptr[3 * 2 + 0] = ibo_ptr[3 * 3 + 0] = m_vbo_index[0] + 8 * m_stroke + 4;
			ibo_ptr[3 * 2 + 2] = ibo_ptr[3 * 3 + 1] = m_vbo_index[0] + 8 * m_stroke + 6;
			//face -x2
			ibo_ptr[3 * 4 + 1] = m_vbo_index[0] + 8 * m_stroke + 1;
			ibo_ptr[3 * 5 + 2] = m_vbo_index[0] + 8 * m_stroke + 4;
			ibo_ptr[3 * 4 + 0] = ibo_ptr[3 * 5 + 0] = m_vbo_index[0] + 8 * m_stroke + 0;
			ibo_ptr[3 * 4 + 2] = ibo_ptr[3 * 5 + 1] = m_vbo_index[0] + 8 * m_stroke + 5;
			//face +x1
			ibo_ptr[3 * 6 + 1] = m_vbo_index[0] + 8 * m_stroke + 2;
			ibo_ptr[3 * 7 + 2] = m_vbo_index[0] + 8 * m_stroke + 5;
			ibo_ptr[3 * 6 + 0] = ibo_ptr[3 * 7 + 0] = m_vbo_index[0] + 8 * m_stroke + 1;
			ibo_ptr[3 * 6 + 2] = ibo_ptr[3 * 7 + 1] = m_vbo_index[0] + 8 * m_stroke + 6;
			//face +x2
			ibo_ptr[3 * 8 + 1] = m_vbo_index[0] + 8 * m_stroke + 3;
			ibo_ptr[3 * 9 + 2] = m_vbo_index[0] + 8 * m_stroke + 6;
			ibo_ptr[3 * 8 + 0] = ibo_ptr[3 * 9 + 0] = m_vbo_index[0] + 8 * m_stroke + 2;
			ibo_ptr[3 * 8 + 2] = ibo_ptr[3 * 9 + 1] = m_vbo_index[0] + 8 * m_stroke + 7;
			//face -x3
			ibo_ptr[3 * 10 + 1] = m_vbo_index[0] + 8 * m_stroke + 0;
			ibo_ptr[3 * 11 + 2] = m_vbo_index[0] + 8 * m_stroke + 7;
			ibo_ptr[3 * 10 + 0] = ibo_ptr[3 * 11 + 0] = m_vbo_index[0] + 8 * m_stroke + 3;
			ibo_ptr[3 * 10 + 2] = ibo_ptr[3 * 11 + 1] = m_vbo_index[0] + 8 * m_stroke + 4;
		}
		void Cube::vbo_stroke_data(void) const
		{
			//data
			vertices::Model3D* vbo_ptr = vbo_data_model_3D();
			//vbo data
			for(uint32_t i = 0; i < 8; i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = positions + 3 * i;
			}
		}
		void Cube::vbo_fill_data(void) const
		{
			//data
			vertices::Model3D* vbo_ptr = vbo_data_model_3D() + 8 * m_stroke;
			//vbo data
			for(uint32_t i = 0; i < 8; i++)
			{
				(vbo_ptr + i)->m_color = m_color_fill;
				(vbo_ptr + i)->m_position = positions + 3 * i;
			}
		}

		//buffers
		void Cube::buffers_size(void)
		{
			m_ibo_size[2] = 36 * m_fill;
			m_ibo_size[1] = 24 * m_stroke;
			m_vbo_size[0] = 8 * (m_stroke + m_fill);
		}
		void Cube::buffers_data(void) const
		{
			if(m_fill) vbo_fill_data();
			if(m_fill) ibo_fill_data();
			if(m_stroke) vbo_stroke_data();
			if(m_stroke) ibo_stroke_data();
		}
	}
}