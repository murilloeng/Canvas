//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Curves/Arc.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Arc::Arc(void) : m_base{1, 0, 0}, m_center{0, 0, 0}, m_normal{0, 0, 1}, m_radius(0), m_angles{0, 0}
		{
			m_fill_colors.resize(1);
			m_stroke_colors.resize(1);
		}

		//destructor
		Arc::~Arc(void)
		{
			return;
		}

		//data
		vec3 Arc::base(const vec3& base)
		{
			return m_base = base;
		}
		vec3 Arc::base(void) const
		{
			return m_base;
		}

		vec3 Arc::center(void) const
		{
			return m_center;
		}
		vec3 Arc::center(const vec3& center)
		{
			return m_center = center;
		}

		vec3 Arc::normal(void) const
		{
			return m_normal;
		}
		vec3 Arc::normal(const vec3& normal)
		{
			return m_normal = normal;
		}

		float Arc::radius(void) const
		{
			return m_radius;
		}
		float Arc::radius(float radius)
		{
			return m_radius = radius;
		}

		float Arc::angle(unsigned index) const
		{
			return m_angles[index];
		}
		float Arc::angle(unsigned index, float angle)
		{
			return m_angles[index] = angle;
		}

		//path
		vec3 Arc::hessian(float s) const
		{
			const vec3 t1 = m_base;
			const vec3 t2 = m_normal.cross(m_base);
			const float t = m_angles[0] + s * (m_angles[1] - m_angles[0]);
			return -m_radius * pow(m_angles[1] - m_angles[0], 2) * (sinf(t) * t2 + cosf(t) * t1);
		}
		vec3 Arc::position(float s) const
		{
			const vec3 t1 = m_base;
			const vec3 t2 = m_normal.cross(m_base);
			const float t = m_angles[0] + s * (m_angles[1] - m_angles[0]);
			return m_center + m_radius * (cosf(t) * t1 + sinf(t) * t2);
		}
		vec3 Arc::gradient(float s) const
		{
			const vec3 t1 = m_base;
			const vec3 t2 = m_normal.cross(m_base);
			const float t = m_angles[0] + s * (m_angles[1] - m_angles[0]);
			return m_radius * (m_angles[1] - m_angles[0]) * (cosf(t) * t2 - sinf(t) * t1);
		}

		//type
		objects::type Arc::type(void) const
		{
			return objects::type::arc;
		}

		//buffers
		unsigned Arc::vbo_size(void) const
		{
			return m_stroke * (m_mesh + 1) + m_fill * (m_mesh + 2);
		}
		unsigned Arc::ibo_size(unsigned index) const
		{
			return (index == 1 || index == 2) * m_mesh;
		}

		//draw
		void Arc::ibo_fill_data(unsigned** ibo_data) const
		{
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_data[2][m_ibo_index[2] + 3 * i + 0] = m_vbo_index + m_stroke * (m_mesh + 1) + 0;
				ibo_data[2][m_ibo_index[2] + 3 * i + 1] = m_vbo_index + m_stroke * (m_mesh + 1) + i + 1;
				ibo_data[2][m_ibo_index[2] + 3 * i + 2] = m_vbo_index + m_stroke * (m_mesh + 1) + i + 2;
			}
		}
		void Arc::ibo_stroke_data(unsigned** ibo_data) const
		{
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_data[1][m_ibo_index[1] + 2 * i + 0] = m_vbo_index + i + 0;
				ibo_data[1][m_ibo_index[1] + 2 * i + 1] = m_vbo_index + i + 1;
			}
		}
		void Arc::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			//data
			vec3 vertex_position;
			const vec3 t2 = m_normal.cross(m_base);
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + m_stroke * (m_mesh + 1);
			//vbo data
			for(unsigned i = 0; i <= m_mesh; i++)
			{
				//position
				const float t = (m_angles[1] - m_angles[0]) * i / m_mesh + m_angles[0];
				vertex_position = m_center + m_radius * (cosf(t) * m_base + sinf(t) * t2);
				//vertices
				(vbo_fill_ptr + i + 1)->m_color = m_fill_colors[0];
				(vbo_fill_ptr + i + 1)->m_position = vertex_position;
			}
			vbo_fill_ptr->m_position = m_center;
			vbo_fill_ptr->m_color = m_fill_colors[0];
		}
		void Arc::vbo_stroke_data(vertices::Vertex* vbo_data) const
		{
			//data
			vec3 vertex_position;
			const vec3 t2 = m_normal.cross(m_base);
			vertices::Model* vbo_stroke_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//vbo data
			for(unsigned i = 0; i <= m_mesh; i++)
			{
				//position
				const float t = (m_angles[1] - m_angles[0]) * i / m_mesh + m_angles[0];
				vertex_position = m_center + m_radius * (cosf(t) * m_base + sinf(t) * t2);
				//vertices
				(vbo_stroke_ptr + i)->m_color = m_stroke_colors[0];
				(vbo_stroke_ptr + i)->m_position = vertex_position;
			}
		}
		void Arc::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			//ibo data
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}