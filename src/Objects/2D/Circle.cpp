//std
#include <cmath>

//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"

#include "Canvas/inc/Objects/2D/Circle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Circle::Circle(void) : m_center{0, 0, 0}, m_normal{0, 0, 1}, m_radius(0)
		{
			return;
		}

		//destructor
		Circle::~Circle(void)
		{
			return;
		}

		//data
		vec3 Circle::center(void) const
		{
			return m_center;
		}
		vec3 Circle::center(const vec3& center)
		{
			return m_center = center;
		}

		vec3 Circle::normal(void) const
		{
			return m_normal;
		}
		vec3 Circle::normal(const vec3& normal)
		{
			return m_normal = normal;
		}

		float Circle::radius(void) const
		{
			return m_radius;
		}
		float Circle::radius(float radius)
		{
			return m_radius = radius;
		}

		uint32_t Circle::mesh(void)
		{
			return m_mesh;
		}
		uint32_t Circle::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		//data
		void Circle::ibo_fill_data(uint32_t** ibo_data) const
		{
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				ibo_data[2][m_ibo_index[2] + 3 * i + 0] = m_vbo_index[0] + m_stroke * m_mesh + 0;
				ibo_data[2][m_ibo_index[2] + 3 * i + 1] = m_vbo_index[0] + m_stroke * m_mesh + 1 + (i + 1) % m_mesh;
				ibo_data[2][m_ibo_index[2] + 3 * i + 2] = m_vbo_index[0] + m_stroke * m_mesh + 1 + (i + 0) % m_mesh;
			}
		}
		void Circle::ibo_stroke_data(uint32_t** ibo_data) const
		{
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				ibo_data[1][m_ibo_index[1] + 2 * i + 0] = m_vbo_index[0] + (i + 0) % m_mesh;
				ibo_data[1][m_ibo_index[1] + 2 * i + 1] = m_vbo_index[0] + (i + 1) % m_mesh;
			}
		}
		void Circle::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			vec3 vertex_position, t1, t2;
			vertices::Model3D* vbo_fill_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0] + m_stroke * m_mesh;
			//vbo data
			m_normal.triad(t1, t2);
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				//position
				const float t = 2 * float(M_PI) * i / m_mesh;
				vertex_position = m_center + m_radius * (cosf(t) * t1 + sinf(t) * t2);
				//vertices
				(vbo_fill_ptr + i + 1)->m_color = m_color_fill;
				(vbo_fill_ptr + i + 1)->m_position = vertex_position;
			}
			vbo_fill_ptr->m_position = m_center;
			vbo_fill_ptr->m_color = m_color_fill;
		}
		void Circle::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			vec3 vertex_position, t1, t2;
			vertices::Model3D* vbo_stroke_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			m_normal.triad(t1, t2);
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				//position
				const float t = 2 * float(M_PI) * i / m_mesh;
				vertex_position = m_center + m_radius * (cosf(t) * t1 + sinf(t) * t2);
				//vertices
				(vbo_stroke_ptr + i)->m_color = m_color_stroke;
				(vbo_stroke_ptr + i)->m_position = vertex_position;
			}
		}

		//buffers
		void Circle::buffers_size(void)
		{
			m_ibo_size[2] = 3 * m_fill * m_mesh;
			m_ibo_size[1] = 2 * m_stroke * m_mesh;
			m_vbo_size[0] = m_stroke * m_mesh + m_fill * (m_mesh + 1);
		}
		void Circle::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}

		//static
		uint32_t Circle::m_mesh = 60;
	}
}