//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Scene/Image.hpp"
#include "Canvas/inc/Vertices/Model2D.hpp"
#include "Canvas/inc/Objects/Image/Palette.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Palette::Palette(void)
		{
			return;
		}

		//destructor
		Palette::~Palette(void)
		{
			return;
		}

		//buffers
		unsigned Palette::vbo_size(unsigned index) const
		{
			return 4 * (index == 3);
		}
		unsigned Palette::ibo_size(unsigned index) const
		{
			return 4 * (index == 7);
		}

		//draw
		void Palette::ibo_fill_data(unsigned** ibo_data) const
		{
			ibo_data[7][m_ibo_index[7] + 2 * 0 + 0] = m_vbo_index[3] + 0;
			ibo_data[7][m_ibo_index[7] + 2 * 0 + 1] = m_vbo_index[3] + 1;
			ibo_data[7][m_ibo_index[7] + 2 * 1 + 0] = m_vbo_index[3] + 1;
			ibo_data[7][m_ibo_index[7] + 2 * 1 + 1] = m_vbo_index[3] + 2;
			ibo_data[7][m_ibo_index[7] + 2 * 2 + 0] = m_vbo_index[3] + 2;
			ibo_data[7][m_ibo_index[7] + 2 * 2 + 1] = m_vbo_index[3] + 3;
			ibo_data[7][m_ibo_index[7] + 2 * 3 + 0] = m_vbo_index[3] + 3;
			ibo_data[7][m_ibo_index[7] + 2 * 3 + 1] = m_vbo_index[3] + 0;
		}
		void Palette::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model2D* vbo_ptr = (vertices::Model2D*) vbo_data[3] + m_vbo_index[3];
			//vbo data
			vbo_ptr[0].m_position = {+0.90f, -0.95f};
			vbo_ptr[1].m_position = {+0.95f, -0.95f};
			vbo_ptr[2].m_position = {+0.95f, +0.95f};
			vbo_ptr[3].m_position = {+0.90f, +0.95f};
			vbo_ptr[0].m_color = Color(1, 1, 1, 1);
			vbo_ptr[1].m_color = Color(1, 1, 1, 1);
			vbo_ptr[2].m_color = Color(1, 1, 1, 1);
			vbo_ptr[3].m_color = Color(1, 1, 1, 1);
		}
		void Palette::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			vbo_fill_data(vbo_data);
			ibo_fill_data(ibo_data);
		}
	}
}