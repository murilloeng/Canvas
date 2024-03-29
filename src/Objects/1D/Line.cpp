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
		vec3 Line::point(unsigned index) const
		{
			return m_points[index];
		}
		vec3 Line::point(unsigned index, const vec3& point)
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
		unsigned Line::vbo_size(unsigned index) const
		{
			return Group::vbo_size(index) + 2 * m_stroke * (index == 0);
		}
		unsigned Line::ibo_size(unsigned index) const
		{
			return Group::ibo_size(index) + (index == 1) * m_stroke;
		}

		//buffers
		void Line::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			unsigned vbo_index = m_vbo_index[0] + Group::vbo_size(0);
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1] + 2 * Group::ibo_size(1);
			//ibo data
			ibo_ptr[0] = vbo_index + 0;
			ibo_ptr[1] = vbo_index + 1;
		}
		void Line::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0] + Group::vbo_size(0);
			//vbo data
			(vbo_ptr + 0)->m_color = m_color_stroke;
			(vbo_ptr + 1)->m_color = m_color_stroke;
			(vbo_ptr + 0)->m_position = m_points[0];
			(vbo_ptr + 1)->m_position = m_points[1];
		}
		void Line::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
			Group::buffers_data(vbo_data, ibo_data);
		}
	}
}