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

		//sizes
		void Line::vbo_size(uint32_t vbo_counter[]) const
		{
			Group::vbo_size(vbo_counter);
			vbo_counter[0] += 2 * m_stroke;
		}
		void Line::ibo_size(uint32_t ibo_counter[]) const
		{
			Group::ibo_size(ibo_counter);
			ibo_counter[1] += 2 * m_stroke;
		}

		//buffers
		void Line::ibo_stroke_data(uint32_t** ibo_data) const
		{
			//data
			uint32_t group_vbo_size[6];
			uint32_t group_ibo_size[12];
			memset(group_vbo_size, 0, sizeof(group_vbo_size));
			memset(group_ibo_size, 0, sizeof(group_ibo_size));
			//offset
			Group::vbo_size(group_vbo_size);
			Group::ibo_size(group_ibo_size);
			const uint32_t vbo_index = m_vbo_index[0] + group_vbo_size[0];
			const uint32_t ibo_index = m_ibo_index[1] + group_ibo_size[1];
			//ibo data
			ibo_data[1][ibo_index + 0] = vbo_index + 0;
			ibo_data[1][ibo_index + 1] = vbo_index + 1;
		}
		void Line::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			uint32_t group_vbo_size[6];
			memset(group_vbo_size, 0, sizeof(group_vbo_size));
			//offset
			Group::vbo_size(group_vbo_size);
			const uint32_t vbo_index = m_vbo_index[0] + group_vbo_size[0];
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data[0] + vbo_index;
			//vbo data
			(vbo_ptr + 0)->m_color = m_color_stroke;
			(vbo_ptr + 1)->m_color = m_color_stroke;
			(vbo_ptr + 0)->m_position = m_points[0];
			(vbo_ptr + 1)->m_position = m_points[1];
		}
		void Line::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
			Group::buffers_data(vbo_data, ibo_data);
		}
	}
}