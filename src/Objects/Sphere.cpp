//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Sphere.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Sphere::Sphere(void) : 
			m_center{0, 0, 0}, m_radius(1.0f), m_draw_color{0, 0, 0, 0}, m_fill_color{0, 0, 0, 0}
		{
			return;
		}

		//destructor
		Sphere::~Sphere(void)
		{
			return;
		}

		//data
		vec3 Sphere::center(void) const
		{
			return m_center;
		}
		vec3 Sphere::center(vec3 center)
		{
			return m_center = center;
		}

		float Sphere::radius(void) const
		{
			return m_radius;
		}
		float Sphere::radius(float radius)
		{
			return m_radius = radius;
		}

		Color Sphere::draw_color(void) const
		{
			return m_draw_color;
		}
		Color Sphere::draw_color(Color draw_color)
		{
			return m_draw_color = draw_color;
		}

		Color Sphere::fill_color(void) const
		{
			return m_fill_color;
		}
		Color Sphere::fill_color(Color fill_color)
		{
			return m_fill_color = fill_color;
		}

		unsigned Sphere::mesh(void)
		{
			return m_mesh;
		}
		unsigned Sphere::mesh(unsigned mesh)
		{
			return m_mesh = mesh;
		}

		//type
		objects::type Sphere::type(void) const
		{
			return objects::type::sphere;
		}

		//buffers
		unsigned Sphere::vbo_size(void) const
		{
			return 
				12 * m_draw + 
				12 * m_fill;
		}
		unsigned Sphere::ibo_size(unsigned index) const
		{
			return 
				30 * (index == 1) * m_draw + 
				20 * (index == 2) * m_fill;
		}

		//draw
		void Sphere::ibo_draw_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//face -x3
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[2 * i + 0] = m_vbo_index + (i + 0) % m_mesh;
				ibo_ptr[2 * i + 1] = m_vbo_index + (i + 1) % m_mesh;
			}
			//face +x3
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[2 * m_mesh + 2 * i + 0] = m_vbo_index + m_mesh + (i + 0) % m_mesh;
				ibo_ptr[2 * m_mesh + 2 * i + 1] = m_vbo_index + m_mesh + (i + 1) % m_mesh;
			}
			//edges
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[4 * m_mesh + 2 * i + 0] = m_vbo_index + i;
				ibo_ptr[4 * m_mesh + 2 * i + 1] = m_vbo_index + i + m_mesh;
			}
		}
		void Sphere::ibo_fill_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[2] + m_ibo_index[2];
			const unsigned vbo_index = m_vbo_index + 2 * m_mesh * m_draw;
			//face -x3
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[3 * i + 0] = vbo_index + 0;
				ibo_ptr[3 * i + 1] = vbo_index + 1 + (i + 0) % m_mesh;
				ibo_ptr[3 * i + 2] = vbo_index + 1 + (i + 1) % m_mesh;
			}
			//face +x3
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[3 * m_mesh + 3 * i + 0] = vbo_index + m_mesh + 1;
				ibo_ptr[3 * m_mesh + 3 * i + 1] = vbo_index + m_mesh + 2 + (i + 0) % m_mesh;
				ibo_ptr[3 * m_mesh + 3 * i + 2] = vbo_index + m_mesh + 2 + (i + 1) % m_mesh;
			}
			//edges
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[6 * m_mesh + 6 * i + 0] = vbo_index + 0 * (m_mesh + 1) + (i + 0) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 1] = vbo_index + 0 * (m_mesh + 1) + (i + 1) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 2] = vbo_index + 1 * (m_mesh + 1) + (i + 1) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 3] = vbo_index + 0 * (m_mesh + 1) + (i + 0) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 4] = vbo_index + 1 * (m_mesh + 1) + (i + 1) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 5] = vbo_index + 1 * (m_mesh + 1) + (i + 0) % m_mesh + 1;
			}
		}
		void Sphere::vbo_draw_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//vbo data
			for(unsigned i = 0; i < m_mesh; i++)
			{
				const float t = 2 * M_PI * i / m_mesh;
				(vbo_ptr + 0 * m_mesh + i)->m_color = m_draw_color;
				(vbo_ptr + 1 * m_mesh + i)->m_color = m_draw_color;
				(vbo_ptr + 0 * m_mesh + i)->m_position = {cosf(t), sinf(t), -1.0f};
				(vbo_ptr + 1 * m_mesh + i)->m_position = {cosf(t), sinf(t), +1.0f};
			}
		}
		void Sphere::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index + 2 * m_mesh * m_draw;
			//vbo data
			for(unsigned i = 0; i < m_mesh; i++)
			{
				const float t = 2 * M_PI * i / m_mesh;
				(vbo_ptr + 0 * (m_mesh + 1) + i + 1)->m_color = m_fill_color;
				(vbo_ptr + 1 * (m_mesh + 1) + i + 1)->m_color = m_fill_color;
				(vbo_ptr + 0 * (m_mesh + 1) + i + 1)->m_position = {cosf(t), sinf(t), -1.0f};
				(vbo_ptr + 1 * (m_mesh + 1) + i + 1)->m_position = {cosf(t), sinf(t), +1.0f};
			}
			(vbo_ptr + 0 * (m_mesh + 1))->m_color = m_fill_color;
			(vbo_ptr + 1 * (m_mesh + 1))->m_color = m_fill_color;
			(vbo_ptr + 0 * (m_mesh + 1))->m_position = {0.0f, 0.0f, -1.0f};
			(vbo_ptr + 1 * (m_mesh + 1))->m_position = {0.0f, 0.0f, +1.0f};
		}
		void Sphere::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			if(m_draw) vbo_draw_data(vbo_data);
			if(m_fill) vbo_fill_data(vbo_data);
			//ibo data
			if(m_draw) ibo_draw_data(ibo_data);
			if(m_fill) ibo_fill_data(ibo_data);
		}

		//static
		unsigned Sphere::m_mesh = 2;
	}
}