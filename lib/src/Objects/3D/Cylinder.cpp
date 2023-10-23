//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/3D/Cylinder.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Cylinder::Cylinder(void) : m_center{0.0f, 0.0f, 0.0f}, m_radius(1.0f), m_height(1.0f)
		{
			return;
		}

		//destructor
		Cylinder::~Cylinder(void)
		{
			return;
		}

		//data
		vec3 Cylinder::center(void) const
		{
			return m_center;
		}
		vec3 Cylinder::center(const vec3& center)
		{
			return m_center = center;
		}

		float Cylinder::radius(void) const
		{
			return m_radius;
		}
		float Cylinder::radius(float radius)
		{
			return m_radius = radius;
		}

		float Cylinder::height(void) const
		{
			return m_height;
		}
		float Cylinder::height(float height)
		{
			return m_height = height;
		}

		unsigned Cylinder::mesh(void)
		{
			return m_mesh;
		}
		unsigned Cylinder::mesh(unsigned mesh)
		{
			return m_mesh = mesh;
		}

		//buffers
		unsigned Cylinder::vbo_size(unsigned index) const
		{
			return (2 * m_mesh * m_stroke + 2 * (m_mesh + 1) * m_fill) * (index == 0);
		}
		unsigned Cylinder::ibo_size(unsigned index) const
		{
			return 3 * m_mesh * (index == 1) * m_stroke + 4 * m_mesh * (index == 2) * m_fill;
		}

		//draw
		void Cylinder::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//face -x3
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[2 * i + 0] = m_vbo_index[0] + (i + 0) % m_mesh;
				ibo_ptr[2 * i + 1] = m_vbo_index[0] + (i + 1) % m_mesh;
			}
			//face +x3
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[2 * m_mesh + 2 * i + 0] = m_vbo_index[0] + m_mesh + (i + 0) % m_mesh;
				ibo_ptr[2 * m_mesh + 2 * i + 1] = m_vbo_index[0] + m_mesh + (i + 1) % m_mesh;
			}
			//edges
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[4 * m_mesh + 2 * i + 0] = m_vbo_index[0] + i;
				ibo_ptr[4 * m_mesh + 2 * i + 1] = m_vbo_index[0] + i + m_mesh;
			}
		}
		void Cylinder::ibo_fill_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[2] + m_ibo_index[2];
			const unsigned vbo_index = m_vbo_index[0] + 2 * m_mesh * m_stroke;
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
		void Cylinder::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			const float r = m_radius;
			const float h = m_height;
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			for(unsigned i = 0; i < m_mesh; i++)
			{
				const float t = 2 * M_PI * i / m_mesh;
				(vbo_ptr + 0 * m_mesh + i)->m_color = m_color_stroke;
				(vbo_ptr + 1 * m_mesh + i)->m_color = m_color_stroke;
				(vbo_ptr + 0 * m_mesh + i)->m_position = m_center + vec3(r * cosf(t), r * sinf(t), -h / 2);
				(vbo_ptr + 1 * m_mesh + i)->m_position = m_center + vec3(r * cosf(t), r * sinf(t), +h / 2);
			}
		}
		void Cylinder::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			const float r = m_radius;
			const float h = m_height;
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0] + 2 * m_mesh * m_stroke;
			//vbo data
			for(unsigned i = 0; i < m_mesh; i++)
			{
				const float t = 2 * M_PI * i / m_mesh;
				(vbo_ptr + 0 * (m_mesh + 1) + i + 1)->m_color = m_color_fill;
				(vbo_ptr + 1 * (m_mesh + 1) + i + 1)->m_color = m_color_fill;
				(vbo_ptr + 0 * (m_mesh + 1) + i + 1)->m_position = m_center + vec3(r * cosf(t), r * sinf(t), -h / 2);
				(vbo_ptr + 1 * (m_mesh + 1) + i + 1)->m_position = m_center + vec3(r * cosf(t), r * sinf(t), +h / 2);
			}
			(vbo_ptr + 0 * (m_mesh + 1))->m_color = m_color_fill;
			(vbo_ptr + 1 * (m_mesh + 1))->m_color = m_color_fill;
			(vbo_ptr + 0 * (m_mesh + 1))->m_position = {0.0f, 0.0f, -m_height / 2};
			(vbo_ptr + 1 * (m_mesh + 1))->m_position = {0.0f, 0.0f, +m_height / 2};
		}
		void Cylinder::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}

		//static
		unsigned Cylinder::m_mesh = 60;
	}
}