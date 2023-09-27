//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Cylinder.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Cylinder::Cylinder(void) : 
			m_draw_color{0, 0, 0, 0}, m_fill_color{0, 0, 0, 0}
		{
			return;
		}

		//destructor
		Cylinder::~Cylinder(void)
		{
			return;
		}

		//data
		Color Cylinder::draw_color(void) const
		{
			return m_draw_color;
		}
		Color Cylinder::draw_color(Color draw_color)
		{
			return m_draw_color = draw_color;
		}

		Color Cylinder::fill_color(void) const
		{
			return m_fill_color;
		}
		Color Cylinder::fill_color(Color fill_color)
		{
			return m_fill_color = fill_color;
		}

		unsigned Cylinder::mesh(void)
		{
			return m_mesh;
		}
		unsigned Cylinder::mesh(unsigned mesh)
		{
			return m_mesh = mesh;
		}

		//type
		objects::type Cylinder::type(void) const
		{
			return objects::type::cylinder;
		}

		//buffers
		unsigned Cylinder::vbo_size(void) const
		{
			return 
				2 * m_mesh * m_draw + 
				2 * (m_mesh + 1) * m_fill;
		}
		unsigned Cylinder::ibo_size(unsigned index) const
		{
			return 
				3 * m_mesh * (index == 1) * m_draw + 
				4 * m_mesh * (index == 2) * m_fill;
		}

		//draw
		void Cylinder::ibo_draw_data(unsigned** ibo_data) const
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
		void Cylinder::ibo_fill_data(unsigned** ibo_data) const
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
		void Cylinder::vbo_draw_data(vertices::Vertex* vbo_data) const
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
		void Cylinder::vbo_fill_data(vertices::Vertex* vbo_data) const
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
		void Cylinder::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			if(m_draw) vbo_draw_data(vbo_data);
			if(m_fill) vbo_fill_data(vbo_data);
			//ibo data
			if(m_draw) ibo_draw_data(ibo_data);
			if(m_fill) ibo_fill_data(ibo_data);
		}

		//static
		unsigned Cylinder::m_mesh = 60;
	}
}