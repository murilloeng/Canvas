//std
#include <cmath>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/2D/Grid_2D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Grid_2D::Grid_2D(void) : m_mesh{10, 10}
		{
			return;
		}

		//destructor
		Grid_2D::~Grid_2D(void)
		{
			return;
		}

		//data
		uint32_t Grid_2D::mesh(uint32_t index) const
		{
			return m_mesh[index];
		}
		uint32_t Grid_2D::mesh(uint32_t index, uint32_t mesh)
		{
			return m_mesh[index] = mesh;
		}

		//data
		void Grid_2D::ibo_stroke_data(void) const
		{
			//data
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			uint32_t vbo_index = m_vbo_index[0];
			uint32_t* ibo_ptr = m_scene->ibo_data(1) + m_ibo_index[1];
			//outer
			for(uint32_t i = 0; i < 4; i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + (i + 0) % 4;
				ibo_ptr[2 * i + 1] = vbo_index + (i + 1) % 4;
			}
			ibo_ptr += 8;
			vbo_index += 4;
			for(uint32_t i = 0; i < n1 - 1; i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + 0 * (n1 - 1) + i;
				ibo_ptr[2 * i + 1] = vbo_index + 1 * (n1 - 1) + i;
			}
			ibo_ptr += 2 * (n1 - 1);
			vbo_index += 2 * (n1 - 1);
			for(uint32_t i = 0; i < n2 - 1; i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + 0 * (n2 - 1) + i;
				ibo_ptr[2 * i + 1] = vbo_index + 1 * (n2 - 1) + i;
			}
		}
		void Grid_2D::ibo_fill_data(void) const
		{
			//data
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			uint32_t* ibo_ptr = m_scene->ibo_data(2) + m_ibo_index[2];
			const uint32_t vbo_index = m_vbo_index[0] + 2 * (n1 + n2) * m_stroke;
			//ibo data
			ibo_ptr[3 * 0 + 0] = vbo_index + 0;
			ibo_ptr[3 * 0 + 1] = vbo_index + 2;
			ibo_ptr[3 * 0 + 2] = vbo_index + 1;
			ibo_ptr[3 * 1 + 0] = vbo_index + 0;
			ibo_ptr[3 * 1 + 1] = vbo_index + 3;
			ibo_ptr[3 * 1 + 2] = vbo_index + 2;
		}
		void Grid_2D::vbo_stroke_data(void) const
		{
			//data
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			const float x1[] = {-1.0f, +1.0f, +1.0f, -1.0f};
			const float x2[] = {-1.0f, -1.0f, +1.0f, +1.0f};
			vertices::Model3D* vbo_ptr = m_scene->vbo_data_model_3D() + m_vbo_index[0];
			//vbo data
			for(uint32_t i = 0; i < 4; i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = {x1[i], x2[i], 0.0f};
			}
			vbo_ptr += 4;
			for(uint32_t i = 0; i < n1 - 1; i++)
			{
				(vbo_ptr + 0 * (n1 - 1) + i)->m_color = m_color_stroke;
				(vbo_ptr + 1 * (n1 - 1) + i)->m_color = m_color_stroke;
				(vbo_ptr + 0 * (n1 - 1) + i)->m_position = {2.0f * (i + 1) / n1 - 1.0f, -1.0f, 0.0f};
				(vbo_ptr + 1 * (n1 - 1) + i)->m_position = {2.0f * (i + 1) / n1 - 1.0f, +1.0f, 0.0f};
			}
			vbo_ptr += 2 * (n1 - 1);
			for(uint32_t i = 0; i < n2 - 1; i++)
			{
				(vbo_ptr + 0 * (n2 - 1) + i)->m_color = m_color_stroke;
				(vbo_ptr + 1 * (n2 - 1) + i)->m_color = m_color_stroke;
				(vbo_ptr + 0 * (n2 - 1) + i)->m_position = {-1.0f, 2.0f * (i + 1) / n2 - 1.0f, 0.0f};
				(vbo_ptr + 1 * (n2 - 1) + i)->m_position = {+1.0f, 2.0f * (i + 1) / n2 - 1.0f, 0.0f};
			}
		}
		void Grid_2D::vbo_fill_data(void) const
		{
			//data
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			const uint32_t ns = 2 * (n1 + n2) * m_stroke;
			const float x1[] = {-1.0f, +1.0f, +1.0f, -1.0f};
			const float x2[] = {-1.0f, -1.0f, +1.0f, +1.0f};
			vertices::Model3D* vbo_ptr = m_scene->vbo_data_model_3D() + m_vbo_index[0] + ns;
			//vbo data
			for(uint32_t i = 0; i < 4; i++)
			{
				vbo_ptr[i].m_color = m_color_fill;
				vbo_ptr[i].m_position = {x1[i], x2[i], 0.0f};
			}
		}

		//buffers
		void Grid_2D::buffers_size(void)
		{
			m_ibo_size[2] = 6 * m_fill;
			m_ibo_size[1] = 2 * (m_mesh[0] + m_mesh[1] + 2) * m_stroke;
			m_vbo_size[0] = 2 * (m_mesh[0] + m_mesh[1]) * m_stroke + 4 * m_fill;
		}
		void Grid_2D::buffers_data(void) const
		{
			if(m_fill) vbo_fill_data();
			if(m_fill) ibo_fill_data();
			if(m_stroke) vbo_stroke_data();
			if(m_stroke) ibo_stroke_data();
		}
	}
}