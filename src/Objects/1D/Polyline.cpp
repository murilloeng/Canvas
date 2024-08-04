//std
#include <cmath>

//canvas
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
			return m_points.size() - 1.0f;
		}
		vec3 Polyline::path_hessian(float s) const
		{
			return {0.0f, 0.0f, 0.0f};
		}
		vec3 Polyline::path_position(float s) const
		{
			uint32_t k = uint32_t(s);
			if(k + 1 == m_points.size()) k--;
			return (1 + k - s) * m_points[k + 0] + (s - k) * m_points[k + 1];
		}
		vec3 Polyline::path_gradient(float s) const
		{
			uint32_t k = uint32_t(s);
			if(k + 1 == m_points.size()) k--;
			return m_points[k + 1] - m_points[k + 0];
		}

		//data
		std::vector<vec3>& Polyline::points(void)
		{
			return m_points;
		}
		const std::vector<vec3>& Polyline::points(void) const
		{
			return m_points;
		}

		//data
		void Polyline::ibo_stroke_data(uint32_t** ibo_data) const
		{
			//data
			const uint32_t nv = (uint32_t) m_points.size();
			uint32_t vbo_index = m_vbo_index[0] + m_vbo_size[0] - nv;
			uint32_t* ibo_ptr = ibo_data[1] + m_ibo_index[1] + m_ibo_size[1] - 2 * (nv - 1);
			//ibo data
			for(uint32_t i = 0; i + 1 < m_points.size(); i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + i + 0;
				ibo_ptr[2 * i + 1] = vbo_index + i + 1;
			}
		}
		void Polyline::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			const uint32_t nv = (uint32_t) m_points.size();
			uint32_t vbo_index = m_vbo_index[0] + m_vbo_size[0] - nv;
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data[0] + vbo_index;
			//vbo data
			for(uint32_t i = 0; i < nv; i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = m_points[i];
			}
		}

		//buffers
		void Polyline::buffers_size(void)
		{
			m_vbo_size[0] = (uint32_t) m_points.size() * m_stroke;
			m_ibo_size[1] = 2 * uint32_t(m_points.size() - 1) * m_stroke;
		}
		void Polyline::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}