//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/1D/Polyline.hpp"

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
			return m_points.size() - 1;
		}
		vec3 Polyline::path_hessian(float s) const
		{
			return {0.0f, 0.0f, 0.0f};
		}
		vec3 Polyline::path_position(float s) const
		{
			unsigned k = unsigned(s);
			if(k + 1 == m_points.size()) k--;
			return (1 + k - s) * m_points[k + 0] + (s - k) * m_points[k + 1];
		}
		vec3 Polyline::path_gradient(float s) const
		{
			unsigned k = unsigned(s);
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

		//buffers
		unsigned Polyline::vbo_size(unsigned index) const
		{
			return Group::vbo_size(index) + m_points.size() * m_stroke * (index == 0);
		}
		unsigned Polyline::ibo_size(unsigned index) const
		{
			return Group::ibo_size(index) + (m_points.size() - 1) * (index == 1) * m_stroke;
		}

		//draw
		void Polyline::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			unsigned vbo_index = m_vbo_index[0] + Group::vbo_size(0);
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1] + 2 * Group::ibo_size(1);
			//ibo data
			for(unsigned i = 0; i + 1 < m_points.size(); i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + i + 0;
				ibo_ptr[2 * i + 1] = vbo_index + i + 1;
			}
		}
		void Polyline::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0] + Group::vbo_size(0);
			//vbo data
			for(unsigned i = 0; i < m_points.size(); i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = m_points[i];
			}
		}
		void Polyline::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
			Group::buffers_data(vbo_data, ibo_data);
		}
	}
}