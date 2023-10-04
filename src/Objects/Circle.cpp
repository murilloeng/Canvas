//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Circle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Circle::Circle(void) : m_radius(0), m_center{0, 0, 0}, m_normal{0, 0, 1}
		{
			m_fill_colors.resize(1);
			m_stroke_colors.resize(1);
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

		unsigned Circle::mesh(void)
		{
			return m_mesh;
		}
		unsigned Circle::mesh(unsigned mesh)
		{
			return m_mesh = mesh;
		}

		//type
		objects::type Circle::type(void) const
		{
			return objects::type::circle;
		}

		//buffers
		unsigned Circle::vbo_size(void) const
		{
			return m_stroke * m_mesh + m_fill * (m_mesh + 1);
		}
		unsigned Circle::ibo_size(unsigned index) const
		{
			return (index == 1 || index == 2) * m_mesh;
		}

		//draw
		void Circle::ibo_fill_data(unsigned** ibo_data) const
		{
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_data[2][m_ibo_index[2] + 3 * i + 0] = m_vbo_index + m_stroke * m_mesh + 0;
				ibo_data[2][m_ibo_index[2] + 3 * i + 1] = m_vbo_index + m_stroke * m_mesh + 1 + (i + 0) % m_mesh;
				ibo_data[2][m_ibo_index[2] + 3 * i + 2] = m_vbo_index + m_stroke * m_mesh + 1 + (i + 1) % m_mesh;
			}
		}
		void Circle::ibo_stroke_data(unsigned** ibo_data) const
		{
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_data[1][m_ibo_index[1] + 2 * i + 0] = m_vbo_index + (i + 0) % m_mesh;
				ibo_data[1][m_ibo_index[1] + 2 * i + 1] = m_vbo_index + (i + 1) % m_mesh;
			}
		}
		void Circle::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			//data
			vec3 vertex_position, t1, t2;
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + m_stroke * m_mesh;
			//vbo data
			m_normal.triad(t1, t2);
			for(unsigned i = 0; i < m_mesh; i++)
			{
				//position
				const float t = 2 * M_PI * i / m_mesh;
				vertex_position = m_center + m_radius * (cosf(t) * t1 + sinf(t) * t2);
				//vertices
				(vbo_fill_ptr + i + 1)->m_color = m_fill_colors[0];
				(vbo_fill_ptr + i + 1)->m_position = vertex_position;
			}
			vbo_fill_ptr->m_position = m_center;
			vbo_fill_ptr->m_color = m_fill_colors[0];
		}
		void Circle::vbo_stroke_data(vertices::Vertex* vbo_data) const
		{
			//data
			vec3 vertex_position, t1, t2;
			vertices::Model* vbo_stroke_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//vbo data
			m_normal.triad(t1, t2);
			for(unsigned i = 0; i < m_mesh; i++)
			{
				//position
				const float t = 2 * M_PI * i / m_mesh;
				vertex_position = m_center + m_radius * (cosf(t) * t1 + sinf(t) * t2);
				//vertices
				(vbo_stroke_ptr + i)->m_color = m_stroke_colors[0];
				(vbo_stroke_ptr + i)->m_position = vertex_position;
			}
		}
		void Circle::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			//ibo data
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}

		//static
		unsigned Circle::m_mesh = 60;
	}
}