//std
#include <cmath>
#include <cstring>

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
			m_center{0, 0, 0}, m_normal{0, 0, 1}, m_draw_color{0, 0, 0}, m_fill_color{0, 0, 0}
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

		float* Circle::center(const float* center)
		{
			return this->center(center[0], center[1], center[2]);
		}
		float* Circle::center(float c1, float c2, float c3)
		{
			m_center[0] = c1;
			m_center[1] = c2;
			m_center[2] = c3;
			return m_center;
		}

		float* Circle::normal(const float* normal)
		{
			return this->normal(normal[0], normal[1], normal[2]);
		}
		float* Circle::normal(float n1, float n2, float n3)
		{
			m_normal[0] = n1;
			m_normal[1] = n2;
			m_normal[2] = n3;
			return m_normal;
		}

		float* Circle::draw_color(const float* draw_color)
		{
			return this->draw_color(draw_color[0], draw_color[1], draw_color[2]);
		}
		float* Circle::draw_color(float c1, float c2, float c3)
		{
			m_draw_color[0] = c1;
			m_draw_color[1] = c2;
			m_draw_color[2] = c3;
			return m_draw_color;
		}

		float* Circle::fill_color(const float* fill_color)
		{
			return this->fill_color(fill_color[0], fill_color[1], fill_color[2]);
		}
		float* Circle::fill_color(float c1, float c2, float c3)
		{
			m_fill_color[0] = c1;
			m_fill_color[1] = c2;
			m_fill_color[2] = c3;
			return m_fill_color;
		}

		const float* Circle::center(void) const
		{
			return m_center;
		}
		const float* Circle::normal(void) const
		{
			return m_normal;
		}
		const float* Circle::draw_color(void) const
		{
			return m_draw_color;
		}
		const float* Circle::fill_color(void) const
		{
			return m_fill_color;
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
			float vertex_position[3], t1[3], t2[3];
			vertices::Model* vbo_draw_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			vertices::Model* vbo_fill_ptr = (vertices::Model*) vbo_data + m_vbo_index + m_draw * m_mesh;
			//vbo data
			triad(m_normal, t1, t2);
			for(unsigned i = 0; i < m_mesh; i++)
			{
				//position
				const float t = 2 * M_PI * i / m_mesh;
				vertex_position[0] = m_center[0] + m_radius * (cos(t) * t1[0] + sin(t) * t2[0]);
				vertex_position[1] = m_center[1] + m_radius * (cos(t) * t1[1] + sin(t) * t2[1]);
				vertex_position[2] = m_center[2] + m_radius * (cos(t) * t1[2] + sin(t) * t2[2]);
				//draw
				if(m_draw)
				{
					memcpy((vbo_draw_ptr + i)->m_color, m_draw_color, 3 * sizeof(float));
					memcpy((vbo_draw_ptr + i)->m_position, vertex_position, 3 * sizeof(float));
				}
				//fill
				if(m_fill)
				{
					memcpy((vbo_fill_ptr + i + 1)->m_color, m_fill_color, 3 * sizeof(float));
					memcpy((vbo_fill_ptr + i + 1)->m_position, vertex_position, 3 * sizeof(float));
				}
				memcpy(vbo_fill_ptr->m_position, m_center, 3 * sizeof(float));
				memcpy(vbo_fill_ptr->m_color, m_fill_color, 3 * sizeof(float));
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