//std
#include <cmath>

//canvas
#include "inc/Utils/math.hpp"

#include "inc/Objects/Arc.hpp"
#include "inc/Objects/Type.hpp"

#include "inc/Vertices/Model.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Arc::Arc(void) : 
			m_base{1, 0, 0}, m_center{0, 0, 0}, m_normal{0, 0, 1}, 
			m_radius(0), m_angles{0, 0}, m_draw_color{0, 0, 0, 0}, m_fill_color{0, 0, 0, 0}
		{
			return;
		}

		//destructor
		Arc::~Arc(void)
		{
			return;
		}

		//data
		vec3 Arc::base(vec3 base)
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
		vec3 Arc::center(vec3 center)
		{
			return m_center = center;
		}

		vec3 Arc::normal(void) const
		{
			return m_normal;
		}
		vec3 Arc::normal(vec3 normal)
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

		Color Arc::draw_color(void) const
		{
			return m_draw_color;
		}
		Color Arc::draw_color(Color draw_color)
		{
			return m_draw_color = draw_color;
		}

		Color Arc::fill_color(void) const
		{
			return m_fill_color;
		}
		Color Arc::fill_color(Color fill_color)
		{
			return m_fill_color = fill_color;
		}

		unsigned Arc::mesh(void)
		{
			return m_mesh;
		}
		unsigned Arc::mesh(unsigned mesh)
		{
			return m_mesh = mesh;
		}

		//type
		objects::type Arc::type(void) const
		{
			return objects::type::arc;
		}

		//misc
		unsigned Arc::current_mesh(void) const
		{
			return fabsf(m_angles[1] - m_angles[0]) / 2 / M_PI * m_mesh;
		}

		//buffers
		unsigned Arc::vbo_size(void) const
		{
			const unsigned mesh = current_mesh();
			return m_draw * (mesh + 1) + m_fill * (mesh + 2);
		}
		unsigned Arc::ibo_size(unsigned index) const
		{
			const unsigned mesh = current_mesh();
			return (index == 1 || index == 2) * mesh;
		}

		//draw
		void Arc::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//data
			vec3 vertex_position;
			const unsigned mesh = current_mesh();
			const vec3 t2 = m_normal.cross(m_base);
			vertices::Model* vbo_draw_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + m_draw * (mesh + 1);
			//vbo data
			for(unsigned i = 0; i <= mesh; i++)
			{
				//position
				const float t = (m_angles[1] - m_angles[0]) * i / mesh + m_angles[0];
				vertex_position = m_center + m_radius * (cosf(t) * m_base + sinf(t) * t2);
				//draw
				if(m_draw)
				{
					(vbo_draw_ptr + i)->m_color = m_draw_color;
					(vbo_draw_ptr + i)->m_position = vertex_position;
				}
				//fill
				if(m_fill)
				{
					(vbo_fill_ptr + i + 1)->m_color = m_fill_color;
					(vbo_fill_ptr + i + 1)->m_position = vertex_position;
				}
				vbo_fill_ptr->m_position = m_center;
				vbo_fill_ptr->m_color = m_fill_color;
			}
			//ibo data
			for(unsigned i = 0; i < mesh; i++)
			{
				if(m_draw)
				{
					ibo_data[1][m_ibo_index[1] + 2 * i + 0] = m_vbo_index + i + 0;
					ibo_data[1][m_ibo_index[1] + 2 * i + 1] = m_vbo_index + i + 1;
				}
				if(m_fill)
				{
					ibo_data[2][m_ibo_index[2] + 3 * i + 0] = m_vbo_index + m_draw * (mesh + 1) + 0;
					ibo_data[2][m_ibo_index[2] + 3 * i + 1] = m_vbo_index + m_draw * (mesh + 1) + i + 1;
					ibo_data[2][m_ibo_index[2] + 3 * i + 2] = m_vbo_index + m_draw * (mesh + 1) + i + 2;
				}
			}
		}

		//static
		unsigned Arc::m_mesh = 60;
	}
}