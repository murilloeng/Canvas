//std
#include <cmath>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/1D/Polyline.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Polyline::Polyline(void)
		{
			return;
		}

		//destructor
		Polyline::~Polyline(void)
		{
			return;
		}

		//path
		float Polyline::path_max(void) const
		{
			return m_vertices.size() - 1.0f;
		}
		vec3 Polyline::path_hessian(float s) const
		{
			return {0.0f, 0.0f, 0.0f};
		}
		vec3 Polyline::path_position(float s) const
		{
			uint32_t k = uint32_t(s);
			if(k + 1 == m_vertices.size()) k--;
			return (1 + k - s) * m_vertices[k + 0] + (s - k) * m_vertices[k + 1];
		}
		vec3 Polyline::path_gradient(float s) const
		{
			uint32_t k = uint32_t(s);
			if(k + 1 == m_vertices.size()) k--;
			return m_vertices[k + 1] - m_vertices[k + 0];
		}

		//data
		std::vector<vec3>& Polyline::vertices(void)
		{
			return m_vertices;
		}
		const std::vector<vec3>& Polyline::vertices(void) const
		{
			return m_vertices;
		}

		//buffers
		void Polyline::buffers_size(void)
		{
			m_vbo_size[0] = (uint32_t) m_vertices.size() * m_stroke;
			m_ibo_size[1] = 2 * uint32_t(m_vertices.size() - 1) * m_stroke;
		}
		void Polyline::buffers_data(void) const
		{
			//data
			if(!m_stroke) return;
			const uint32_t nv = (uint32_t) m_vertices.size();
			uint32_t* ibo_ptr = m_scene->ibo_data(1) + m_ibo_index[1];
			vertices::Model3D* vbo_ptr = m_scene->vbo_data_model_3D() + m_vbo_index[0];
			//vbo data
			for(uint32_t i = 0; i < nv; i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = m_vertices[i];
			}
			//ibo data
			for(uint32_t i = 0; i + 1 < m_vertices.size(); i++)
			{
				ibo_ptr[2 * i + 0] = m_vbo_index[0] + i + 0;
				ibo_ptr[2 * i + 1] = m_vbo_index[0] + i + 1;
			}
		}
	}
}