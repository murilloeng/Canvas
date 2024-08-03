//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/2D/Surface.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Surface::Surface(void) : m_domain{0, 1, 0, 1}, m_mesh{10, 10}
		{
			return;
		}

		//destructor
		Surface::~Surface(void)
		{
			return;
		}

		//data
		uint32_t Surface::mesh(uint32_t index) const
		{
			return m_mesh[index];
		}
		uint32_t Surface::mesh(uint32_t index, uint32_t mesh)
		{
			return m_mesh[index] = mesh;
		}

		float Surface::domain(uint32_t i, uint32_t j) const
		{
			return m_domain[2 * i + j];
		}
		float Surface::domain(uint32_t i, uint32_t j, float domain)
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

		//data
		void Surface::ibo_fill_data(uint32_t** ibo_data) const
		{
			//data
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			uint32_t* ibo_ptr = ibo_data[2] + m_ibo_index[2];
			uint32_t vbo_index = m_vbo_index[0] + (n1 + 1) * (n2 + 1) * m_stroke;
			//ibo data
			for(uint32_t i = 0; i < n2; i++)
			{
				for(uint32_t j = 0; j < n1; j++)
				{
					ibo_ptr[0] = vbo_index + (n1 + 1) * (i + 0) + j + 0;
					ibo_ptr[1] = vbo_index + (n1 + 1) * (i + 0) + j + 1;
					ibo_ptr[2] = vbo_index + (n1 + 1) * (i + 1) + j + 0;
					ibo_ptr[3] = vbo_index + (n1 + 1) * (i + 0) + j + 1;
					ibo_ptr[4] = vbo_index + (n1 + 1) * (i + 1) + j + 1;
					ibo_ptr[5] = vbo_index + (n1 + 1) * (i + 1) + j + 0;
					ibo_ptr += 6;
				}
			}
		}
		void Surface::ibo_stroke_data(uint32_t** ibo_data) const
		{
			//data
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			uint32_t vbo_index = m_vbo_index[0];
			uint32_t* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//ibo data
			for(uint32_t i = 0; i <= n2; i++)
			{
				for(uint32_t j = 0; j < n1; j++)
				{
					ibo_ptr[0] = vbo_index + (n1 + 1) * (i + 0) + j + 0;
					ibo_ptr[1] = vbo_index + (n1 + 1) * (i + 0) + j + 1;
					ibo_ptr += 2;
				}
			}
			for(uint32_t i = 0; i < n2; i++)
			{
				for(uint32_t j = 0; j <= n1; j++)
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
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0] + (n1 + 1) * (n2 + 1) * m_stroke;
			//vbo data
			for(uint32_t i = 0; i <= n2; i++)
			{
				for(uint32_t j = 0; j <= n1; j++)
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
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			for(uint32_t i = 0; i <= n2; i++)
			{
				for(uint32_t j = 0; j <= n1; j++)
				{
					const float s1 = a1 + (b1 - a1) * j / n1;
					const float s2 = a2 + (b2 - a2) * i / n2;
					(vbo_ptr + (n1 + 1) * i + j)->m_color = m_color_stroke;
					(vbo_ptr + (n1 + 1) * i + j)->m_position = m_position(s1, s2);
				}
			}
		}

		//buffers
		void Surface::buffers_size(void)
		{
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			m_ibo_size[2] = 6 * n1 * n2 * m_fill;
			m_ibo_size[1] = 2 * (n1 + n2 + 2 * n1 * n2) * m_stroke;
			m_vbo_size[0] = (n1 + 1) * (n2 + 1) * (m_stroke + m_fill);
		}
		void Surface::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}