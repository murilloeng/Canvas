//std
#include <cmath>

//canvas
#include "Canvas/lib/inc/Vertices/Model.hpp"

#include "Canvas/lib/inc/Objects/2D/Grid_2D.hpp"

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
		unsigned Grid_2D::mesh(unsigned index) const
		{
			return m_mesh[index];
		}
		unsigned Grid_2D::mesh(unsigned index, unsigned mesh)
		{
			return m_mesh[index] = mesh;
		}

		//buffers
		unsigned Grid_2D::vbo_size(unsigned index) const
		{
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			return (2 * (n1 + n2) * m_stroke + 4 * m_fill) * (index == 0);
		}
		unsigned Grid_2D::ibo_size(unsigned index) const
		{
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			return (n1 + n2 + 2) * (index == 1) * m_stroke + 2 * (index == 2) * m_fill;
		}

		//draw
		void Grid_2D::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			unsigned vbo_index = m_vbo_index[0];
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//outer
			for(unsigned i = 0; i < 4; i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + (i + 0) % 4;
				ibo_ptr[2 * i + 1] = vbo_index + (i + 1) % 4;
			}
			ibo_ptr += 8;
			vbo_index += 4;
			for(unsigned i = 0; i < n1 - 1; i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + 0 * (n1 - 1) + i;
				ibo_ptr[2 * i + 1] = vbo_index + 1 * (n1 - 1) + i;
			}
			ibo_ptr += 2 * (n1 - 1);
			vbo_index += 2 * (n1 - 1);
			for(unsigned i = 0; i < n2 - 1; i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + 0 * (n2 - 1) + i;
				ibo_ptr[2 * i + 1] = vbo_index + 1 * (n2 - 1) + i;
			}
		}
		void Grid_2D::ibo_fill_data(unsigned** ibo_data) const
		{
			//data
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			unsigned* ibo_ptr = ibo_data[2] + m_ibo_index[2];
			const unsigned vbo_index = m_vbo_index[0] + 2 * (n1 + n2) * m_stroke;
			//ibo data
			ibo_ptr[3 * 0 + 0] = vbo_index + 0;
			ibo_ptr[3 * 0 + 1] = vbo_index + 2;
			ibo_ptr[3 * 0 + 2] = vbo_index + 1;
			ibo_ptr[3 * 1 + 0] = vbo_index + 0;
			ibo_ptr[3 * 1 + 1] = vbo_index + 3;
			ibo_ptr[3 * 1 + 2] = vbo_index + 2;
		}
		void Grid_2D::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			const float x1[] = {-1.0f, +1.0f, +1.0f, -1.0f};
			const float x2[] = {-1.0f, -1.0f, +1.0f, +1.0f};
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			for(unsigned i = 0; i < 4; i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = {x1[i], x2[i], 0.0f};
			}
			vbo_ptr += 4;
			for(unsigned i = 0; i < n1 - 1; i++)
			{
				(vbo_ptr + 0 * (n1 - 1) + i)->m_color = m_color_stroke;
				(vbo_ptr + 1 * (n1 - 1) + i)->m_color = m_color_stroke;
				(vbo_ptr + 0 * (n1 - 1) + i)->m_position = {2.0f * (i + 1) / n1 - 1.0f, -1.0f, 0.0f};
				(vbo_ptr + 1 * (n1 - 1) + i)->m_position = {2.0f * (i + 1) / n1 - 1.0f, +1.0f, 0.0f};
			}
			vbo_ptr += 2 * (n1 - 1);
			for(unsigned i = 0; i < n2 - 1; i++)
			{
				(vbo_ptr + 0 * (n2 - 1) + i)->m_color = m_color_stroke;
				(vbo_ptr + 1 * (n2 - 1) + i)->m_color = m_color_stroke;
				(vbo_ptr + 0 * (n2 - 1) + i)->m_position = {-1.0f, 2.0f * (i + 1) / n2 - 1.0f, 0.0f};
				(vbo_ptr + 1 * (n2 - 1) + i)->m_position = {+1.0f, 2.0f * (i + 1) / n2 - 1.0f, 0.0f};
			}
		}
		void Grid_2D::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			const float x1[] = {-1.0f, +1.0f, +1.0f, -1.0f};
			const float x2[] = {-1.0f, -1.0f, +1.0f, +1.0f};
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0] + 2 * (n1 + n2) * m_stroke;
			//vbo data
			for(unsigned i = 0; i < 4; i++)
			{
				(vbo_ptr + i)->m_color = m_color_fill;
				(vbo_ptr + i)->m_position = {x1[i], x2[i], 0.0f};
			}
		}
		void Grid_2D::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}