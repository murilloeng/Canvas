//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/1D/Line.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Line::Line(void) : m_points{{0, 0, 0}, {0, 0, 0}}
		{
			return;
		}

		//destructor
		Line::~Line(void)
		{
			return;
		}

		//data
		vec3 Line::point(uint32_t index) const
		{
			return m_points[index];
		}
		vec3 Line::point(uint32_t index, const vec3& point)
		{
			return m_points[index] = point;
		}

		//path
		vec3 Line::path_hessian(float s) const
		{
			return {0, 0, 0};
		}
		vec3 Line::path_position(float s) const
		{
			return m_points[0] + s * (m_points[1] - m_points[0]);
		}
		vec3 Line::path_gradient(float s) const
		{
			return m_points[1] - m_points[0];
		}

		//data
		void Line::ibo_stroke_data(uint32_t** ibo_data) const
		{
			//data
			uint32_t vbo_index = m_vbo_index[0] + m_vbo_size[0] - 2;
			uint32_t* ibo_ptr = ibo_data[1] + m_ibo_index[1] + m_ibo_size[1] - 2;
			//ibo data
			ibo_ptr[0] = vbo_index + 0;
			ibo_ptr[1] = vbo_index + 1;
		}
		void Line::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			uint32_t vbo_index = m_vbo_index[0] + m_vbo_size[0] - 2;
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data[0] + vbo_index;
			//vbo data
			(vbo_ptr + 0)->m_color = m_color_stroke;
			(vbo_ptr + 1)->m_color = m_color_stroke;
			(vbo_ptr + 0)->m_position = m_points[0];
			(vbo_ptr + 1)->m_position = m_points[1];
		}

		//buffers
		void Line::buffers_size(void)
		{
			Group::buffers_size();
			m_vbo_size[0] += 2 * m_stroke;
			m_ibo_size[1] += 2 * m_stroke;
		}
		void Line::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
			Group::buffers_data(vbo_data, ibo_data);
		}
	}
}