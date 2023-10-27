//canvas
#include "inc/Vertices/Model.hpp"
#include "inc/Objects/2D/Surface.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Surface::Surface(void) : m_mesh{10, 10}, m_domain{0, 1, 0, 1}
		{
			return;
		}

		//destructor
		Surface::~Surface(void)
		{
			return;
		}

		//data
		unsigned Surface::mesh(unsigned index) const
		{
			return m_mesh[index];
		}
		unsigned Surface::mesh(unsigned index, unsigned mesh)
		{
			return m_mesh[index] = mesh;
		}

		float Surface::domain(unsigned i, unsigned j) const
		{
			return m_domain[2 * i + j];
		}
		float Surface::domain(unsigned i, unsigned j, float domain)
		{
			return m_domain[2 * i + j] = domain;
		}

		std::function<vec3(float, float)> Surface::position(void) const
		{
			return m_position;
		}
		std::function<vec3(float, float)> Surface::position(std::function<vec3(float, float)> position)
		{
			return m_position = position;
		}

		//buffers
		unsigned Surface::vbo_size(unsigned index) const
		{
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			return (n1 + 1) * (n2 + 1) * (m_stroke + m_fill) * (index == 0);
		}
		unsigned Surface::ibo_size(unsigned index) const
		{
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			return (n1 + n2 + 2 * n1 * n2) * m_stroke * (index == 1) + 2 * n1 * n2 * m_fill * (index == 2);
		}

		//draw
		void Surface::ibo_fill_data(unsigned** ibo_data) const
		{
			//data
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			unsigned* ibo_ptr = ibo_data[2] + m_ibo_index[2];
			unsigned vbo_index = m_vbo_index[0] + (n1 + 1) * (n2 + 1) * m_stroke;
			//ibo data
			for(unsigned i = 0; i < n2; i++)
			{
				for(unsigned j = 0; j < n1; j++)
				{
					ibo_ptr[0] = vbo_index + (n1 + 1) * (i + 0) + j + 0;
					ibo_ptr[1] = vbo_index + (n1 + 1) * (i + 1) + j + 0;
					ibo_ptr[2] = vbo_index + (n1 + 1) * (i + 0) + j + 1;
					ibo_ptr[3] = vbo_index + (n1 + 1) * (i + 0) + j + 1;
					ibo_ptr[4] = vbo_index + (n1 + 1) * (i + 1) + j + 0;
					ibo_ptr[5] = vbo_index + (n1 + 1) * (i + 1) + j + 1;
					ibo_ptr += 6;
				}
			}
		}
		void Surface::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			unsigned vbo_index = m_vbo_index[0];
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//ibo data
			for(unsigned i = 0; i <= n2; i++)
			{
				for(unsigned j = 0; j < n1; j++)
				{
					ibo_ptr[0] = vbo_index + (n1 + 1) * (i + 0) + j + 0;
					ibo_ptr[1] = vbo_index + (n1 + 1) * (i + 0) + j + 1;
					ibo_ptr += 2;
				}
			}
			for(unsigned i = 0; i < n2; i++)
			{
				for(unsigned j = 0; j <= n1; j++)
				{
					ibo_ptr[0] = vbo_index + (n1 + 1) * (i + 0) + j + 0;
					ibo_ptr[1] = vbo_index + (n1 + 1) * (i + 1) + j + 0;
					ibo_ptr += 2;
				}
			}
		}
		void Surface::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			const float a1 = m_domain[0];
			const float b1 = m_domain[1];
			const float a2 = m_domain[2];
			const float b2 = m_domain[3];
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0] + (n1 + 1) * (n2 + 1) * m_stroke;
			//vbo data
			for(unsigned i = 0; i <= n2; i++)
			{
				for(unsigned j = 0; j <= n1; j++)
				{
					const float s1 = a1 + (b1 - a1) * j / n1;
					const float s2 = a2 + (b2 - a2) * i / n2;
					(vbo_ptr + (n1 + 1) * i + j)->m_color = m_color_fill;
					(vbo_ptr + (n1 + 1) * i + j)->m_position = m_position(s1, s2);
				}
			}
		}
		void Surface::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			const float a1 = m_domain[0];
			const float b1 = m_domain[1];
			const float a2 = m_domain[2];
			const float b2 = m_domain[3];
			const unsigned n1 = m_mesh[0];
			const unsigned n2 = m_mesh[1];
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			for(unsigned i = 0; i <= n2; i++)
			{
				for(unsigned j = 0; j <= n1; j++)
				{
					const float s1 = a1 + (b1 - a1) * j / n1;
					const float s2 = a2 + (b2 - a2) * i / n2;
					(vbo_ptr + (n1 + 1) * i + j)->m_color = m_color_stroke;
					(vbo_ptr + (n1 + 1) * i + j)->m_position = m_position(s1, s2);
				}
			}
		}
		void Surface::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}