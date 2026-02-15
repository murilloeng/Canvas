//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Surface.hpp"

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
		void Surface::ibo_data(uint32_t* ibo_ptr) const
		{
			//data
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			//ibo faces data
			for(uint32_t i = 0; i < n2; i++)
			{
				for(uint32_t j = 0; j < n1; j++)
				{
					ibo_ptr[0] = (n1 + 1) * (i + 0) + j + 0;
					ibo_ptr[1] = (n1 + 1) * (i + 0) + j + 1;
					ibo_ptr[2] = (n1 + 1) * (i + 1) + j + 0;
					ibo_ptr[3] = (n1 + 1) * (i + 0) + j + 1;
					ibo_ptr[4] = (n1 + 1) * (i + 1) + j + 1;
					ibo_ptr[5] = (n1 + 1) * (i + 1) + j + 0;
					ibo_ptr += 6;
				}
			}
			//ibo edges data
			for(uint32_t i = 0; i <= n2; i++)
			{
				for(uint32_t j = 0; j < n1; j++)
				{
					ibo_ptr[0] = (n1 + 1) * (i + 0) + j + 0;
					ibo_ptr[1] = (n1 + 1) * (i + 0) + j + 1;
					ibo_ptr += 2;
				}
			}
			for(uint32_t i = 0; i < n2; i++)
			{
				for(uint32_t j = 0; j <= n1; j++)
				{
					ibo_ptr[0] = (n1 + 1) * (i + 0) + j + 0;
					ibo_ptr[1] = (n1 + 1) * (i + 1) + j + 0;
					ibo_ptr += 2;
				}
			}
		}
		void Surface::vbo_data(vertices::Model3D* vbo_ptr) const
		{
			//data
			const float a1 = m_domain[0];
			const float b1 = m_domain[1];
			const float a2 = m_domain[2];
			const float b2 = m_domain[3];
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			const unsigned ns = (n1 + 1) * (n2 + 1);
			//vbo data
			for(uint32_t i = 0; i <= n2; i++)
			{
				for(uint32_t j = 0; j <= n1; j++)
				{
					const float s1 = a1 + (b1 - a1) * j / n1;
					const float s2 = a2 + (b2 - a2) * i / n2;
					vbo_ptr[(n1 + 1) * i + j].m_color = m_color_fill;
					vbo_ptr[(n1 + 1) * i + j + ns].m_color = m_color_stroke;
					vbo_ptr[(n1 + 1) * i + j].m_position = m_position(s1, s2);
					vbo_ptr[(n1 + 1) * i + j + ns].m_position = m_position(s1, s2);
				}
			}
		}

		//buffers
		void Surface::setup(void)
		{
			//data
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			//allocate
			m_vbo.allocate(2 * (n1 + 1) * (n2 + 1));
			m_ibo.allocate(2 * (n1 + n2 + 5 * n1 * n2));
			//buffers data
			uint32_t* ibo_ptr = m_ibo.data();
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//buffers data
			ibo_data(ibo_ptr);
			vbo_data(vbo_ptr);
			//transfer
			m_vbo.transfer();
			m_ibo.transfer();
		}
		void Surface::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			const uint32_t n1 = m_mesh[0];
			const uint32_t n2 = m_mesh[1];
			const unsigned ns = (n1 + 1) * (n2 + 1);
			glDrawElements(GL_TRIANGLES, 6 * n1 * n2, GL_UNSIGNED_INT, nullptr);
			glDrawElementsBaseVertex(GL_LINES, 2 * (n1 + n2 + 2 * n1 * n2), GL_UNSIGNED_INT, (void*) (6 * n1 * n2 * sizeof(uint32_t)), ns);
		}
	}
}