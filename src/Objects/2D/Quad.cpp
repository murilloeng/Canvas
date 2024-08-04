//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/2D/Quad.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Quad::Quad(void) : m_points{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
		{
			return;
		}

		//destructor
		Quad::~Quad(void)
		{
			return;
		}

		//data
		vec3 Quad::point(uint32_t index) const
		{
			return m_points[index];
		}
		vec3 Quad::point(uint32_t index, const vec3& position)
		{
			return m_points[index] = position;
		}

		//data
		void Quad::ibo_fill_data(void) const
		{
			//data
			uint32_t* ibo_ptr = m_scene->ibo_data(2) + m_ibo_index[2];
			//ibo data
			ibo_ptr[0] = m_vbo_index[0] + 4 * m_stroke + 0;
			ibo_ptr[1] = m_vbo_index[0] + 4 * m_stroke + 2;
			ibo_ptr[2] = m_vbo_index[0] + 4 * m_stroke + 1;
			ibo_ptr[3] = m_vbo_index[0] + 4 * m_stroke + 0;
			ibo_ptr[4] = m_vbo_index[0] + 4 * m_stroke + 3;
			ibo_ptr[5] = m_vbo_index[0] + 4 * m_stroke + 2;
		}
		void Quad::ibo_stroke_data(void) const
		{
			//data
			uint32_t* ibo_ptr = m_scene->ibo_data(1) + m_ibo_index[1];
			//ibo data
			ibo_ptr[0] = ibo_ptr[7] = m_vbo_index[0] + 0;
			ibo_ptr[1] = ibo_ptr[2] = m_vbo_index[0] + 1;
			ibo_ptr[3] = ibo_ptr[4] = m_vbo_index[0] + 2;
			ibo_ptr[5] = ibo_ptr[6] = m_vbo_index[0] + 3;
		}
		void Quad::vbo_fill_data(void) const
		{
			//data
			const uint32_t ns = 4 * m_stroke;
			vertices::Model3D* vbo_fill_ptr = m_scene->vbo_data_model_3D() + m_vbo_index[0] + ns;
			//vbo data
			for(uint32_t i = 0; i < 4; i++)
			{
				(vbo_fill_ptr + i)->m_color = m_color_fill;
				(vbo_fill_ptr + i)->m_position = m_points[i];
			}
		}
		void Quad::vbo_stroke_data(void) const
		{
			//data
			vertices::Model3D* vbo_stroke_ptr = m_scene->vbo_data_model_3D() + m_vbo_index[0];
			//vbo data
			for(uint32_t i = 0; i < 4; i++)
			{
				(vbo_stroke_ptr + i)->m_color = m_color_stroke;
				(vbo_stroke_ptr + i)->m_position = m_points[i];
			}
		}

		//buffers
		void Quad::buffers_size(void)
		{
			m_ibo_size[2] = 6 * m_fill;
			m_ibo_size[1] = 8 * m_stroke;
			m_vbo_size[0] = 4 * (m_stroke + m_fill);
		}
		void Quad::buffers_data(void) const
		{
			if(m_fill) vbo_fill_data();
			if(m_fill) ibo_fill_data();
			if(m_stroke) vbo_stroke_data();
			if(m_stroke) ibo_stroke_data();
		}
	}
}