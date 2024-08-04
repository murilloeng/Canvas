//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"

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

		//buffers
		void Line::buffers_size(void)
		{
			m_vbo_size[0] = 2 * m_stroke;
			m_ibo_size[1] = 2 * m_stroke;
		}
		void Line::buffers_data(void) const
		{
			//data
			if(!m_stroke) return;
			uint32_t* ibo_ptr = ibo_data(1);
			vertices::Model3D* vbo_ptr = vbo_data_model_3D();
			//ibo data
			ibo_ptr[0] = m_vbo_index[0] + 0;
			ibo_ptr[1] = m_vbo_index[0] + 1;
			//vbo data
			vbo_ptr[0].m_color = m_color_stroke;
			vbo_ptr[1].m_color = m_color_stroke;
			vbo_ptr[0].m_position = m_points[0];
			vbo_ptr[1].m_position = m_points[1];
		}
	}
}