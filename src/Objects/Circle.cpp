//std
#include <cmath>

//canvas
#include "inc/Utils/math.hpp"

#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Circle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Circle::Circle(void) : 
			m_draw(false), m_fill(false), m_radius(0),
			m_center{0, 0, 0}, m_normal{0, 0, 1}, m_draw_color{0, 0, 0, 0}, m_fill_color{0, 0, 0, 0}
		{
			return;
		}

		//destructor
		Circle::~Circle(void)
		{
			return;
		}

		//data
		bool Circle::draw(bool draw)
		{
			return m_draw = draw;
		}
		bool Circle::draw(void) const
		{
			return m_draw;
		}

		bool Circle::fill(bool fill)
		{
			return m_fill = fill;
		}
		bool Circle::fill(void) const
		{
			return m_fill;
		}

		vec3 Circle::center(void) const
		{
			return m_center;
		}
		vec3 Circle::center(vec3 center)
		{
			return m_center = center;
		}

		vec3 Circle::normal(void) const
		{
			return m_normal;
		}
		vec3 Circle::normal(vec3 normal)
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

		Color Circle::draw_color(void) const
		{
			return m_draw_color;
		}
		Color Circle::draw_color(Color draw_color)
		{
			return m_draw_color = draw_color;
		}

		Color Circle::fill_color(void) const
		{
			return m_fill_color;
		}
		Color Circle::fill_color(Color fill_color)
		{
			return m_fill_color = fill_color;
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
			return m_draw * m_mesh + m_fill * (m_mesh + 1);
		}
		unsigned Circle::ibo_size(unsigned index) const
		{
			return (index == 1 || index == 2) * m_mesh;
		}

		//draw
		void Circle::draw(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//data
			vec3 vertex_position, t1, t2;
			vertices::Model* vbo_draw_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + m_draw * m_mesh;
			//vbo data
			m_normal.triad(t1, t2);
			for(unsigned i = 0; i < m_mesh; i++)
			{
				//position
				const float t = 2 * M_PI * i / m_mesh;
				vertex_position = m_center + m_radius * (cosf(t) * t1 + sinf(t) * t2);
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
			for(unsigned i = 0; i < m_mesh; i++)
			{
				if(m_draw)
				{
					ibo_data[1][m_ibo_index[1] + 2 * i + 0] = m_vbo_index + (i + 0) % m_mesh;
					ibo_data[1][m_ibo_index[1] + 2 * i + 1] = m_vbo_index + (i + 1) % m_mesh;
				}
				if(m_fill)
				{
					ibo_data[2][m_ibo_index[2] + 3 * i + 0] = m_vbo_index + m_draw * m_mesh + 0;
					ibo_data[2][m_ibo_index[2] + 3 * i + 1] = m_vbo_index + m_draw * m_mesh + 1 + (i + 0) % m_mesh;
					ibo_data[2][m_ibo_index[2] + 3 * i + 2] = m_vbo_index + m_draw * m_mesh + 1 + (i + 1) % m_mesh;
				}
			}
		}

		//static
		unsigned Circle::m_mesh = 60;
	}
}