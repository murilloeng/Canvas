//std
#include <cmath>
#include <cfloat>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/2D/Polygon.hpp"
#include "Canvas/inc/Objects/Tessellator.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Polygon::Polygon(void)
		{
			return;
		}

		//destructor
		Polygon::~Polygon(void)
		{
			return;
		}

		//data
		std::vector<vec2>& Polygon::vertices(void)
		{
			return m_vertices;
		}
		const std::vector<vec2>& Polygon::vertices(void) const
		{
			return m_vertices;
		}

		std::vector<uint32_t>& Polygon::loops(void)
		{
			return m_loops;
		}
		const std::vector<uint32_t>& Polygon::loops(void) const
		{
			return m_loops;
		}

		//data
		void Polygon::ibo_fill_data(void) const
		{
			//data
			const uint32_t nl = (uint32_t) m_loops.size();
			const uint32_t nv = (uint32_t) m_vertices.size();
			uint32_t vbo_index = m_vbo_index[0] + nv * m_stroke;
			uint32_t* ibo_ptr = m_scene->ibo_data(2) + m_ibo_index[2];
			uint32_t* triangles = (uint32_t*) alloca(3 * (nv + 2 * nl - 6) * sizeof(uint32_t));
			//tessellation
			Tessellator(m_vertices.data(), m_loops.data(), nl - 1, triangles).tessellate();
			//ibo data
			for(uint32_t i = 0; i < nv + 2 * nl - 6; i++)
			{
				ibo_ptr[0] = vbo_index + triangles[3 * i + 0];
				ibo_ptr[1] = vbo_index + triangles[3 * i + 2];
				ibo_ptr[2] = vbo_index + triangles[3 * i + 1];
				ibo_ptr += 3;
			}
		}
		void Polygon::vbo_fill_data(void) const
		{
			//data
			const uint32_t nv = (uint32_t) m_vertices.size();
			vertices::Model3D* vbo_ptr = m_scene->vbo_data_model_3D() + m_vbo_index[0];
			//vbo data
			vbo_ptr += nv * m_stroke;
			for(uint32_t i = 0; i < nv; i++)
			{
				(vbo_ptr + i)->m_color = m_color_fill;
				(vbo_ptr + i)->m_position = {m_vertices[i][0], m_vertices[i][1], 0};
			}
		}
		void Polygon::ibo_stroke_data(void) const
		{
			//data
			uint32_t* ibo_ptr = m_scene->ibo_data(1) + m_ibo_index[1];
			//ibo data
			for(uint32_t i = 0; i + 1 < m_loops.size(); i++)
			{
				const uint32_t ls = m_loops[i + 1] - m_loops[i];
				for(uint32_t j = m_loops[i]; j < m_loops[i + 1]; j++)
				{
					ibo_ptr[0] = m_vbo_index[0] + m_loops[i] + (j + 0 - m_loops[i]) % ls;
					ibo_ptr[1] = m_vbo_index[0] + m_loops[i] + (j + 1 - m_loops[i]) % ls;
					ibo_ptr += 2;
				}
			}
		}
		void Polygon::vbo_stroke_data(void) const
		{
			//data
			const uint32_t nv = (uint32_t) m_vertices.size();
			vertices::Model3D* vbo_ptr = m_scene->vbo_data_model_3D() + m_vbo_index[0];
			//vbo data
			for(uint32_t i = 0; i < nv; i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = {m_vertices[i][0], m_vertices[i][1], 0};
			}
		}

		//buffers
		void Polygon::buffers_size(void)
		{
			//data
			const uint32_t nl = (uint32_t) m_loops.size();
			const uint32_t nv = (uint32_t) m_vertices.size();
			//size
			m_ibo_size[1] = 2 * nv * m_stroke;
			m_vbo_size[0] = nv * (m_stroke + m_fill);
			m_ibo_size[2] = 3 * (nv + 2 * nl - 6) * m_fill;
		}
		void Polygon::buffers_data(void) const
		{
			if(m_fill) vbo_fill_data();
			if(m_fill) ibo_fill_data();
			if(m_stroke) vbo_stroke_data();
			if(m_stroke) ibo_stroke_data();
		}
	}
}