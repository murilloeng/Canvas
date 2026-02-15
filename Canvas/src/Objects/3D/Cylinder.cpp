//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Cylinder.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Cylinder::Cylinder(void) : m_color_fill{"blue"}, m_color_stroke{"white"}
		{
			return;
		}

		//destructor
		Cylinder::~Cylinder(void)
		{
			return;
		}

		//data
		uint32_t Cylinder::mesh(void)
		{
			return m_mesh;
		}
		uint32_t Cylinder::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		Color Cylinder::color_fill(void) const
		{
			return m_color_fill;
		}
		Color Cylinder::color_fill(const Color& color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color Cylinder::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color Cylinder::color_stroke(const Color& color_stroke)
		{
			return m_color_stroke = color_stroke;
		}

		//buffers data
		void Cylinder::ibo_edges_data(uint32_t* ibo_ptr) const
		{
			//face -x3
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				ibo_ptr[2 * i + 0] = (i + 0) % m_mesh;
				ibo_ptr[2 * i + 1] = (i + 1) % m_mesh;
			}
			//face +x3
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				ibo_ptr[2 * m_mesh + 2 * i + 0] = m_mesh + (i + 0) % m_mesh;
				ibo_ptr[2 * m_mesh + 2 * i + 1] = m_mesh + (i + 1) % m_mesh;
			}
			//edges
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				ibo_ptr[4 * m_mesh + 2 * i + 0] = i;
				ibo_ptr[4 * m_mesh + 2 * i + 1] = i + m_mesh;
			}
		}
		void Cylinder::ibo_faces_data(uint32_t* ibo_ptr) const
		{
			//face -x3
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				ibo_ptr[3 * i + 0] = 0;
				ibo_ptr[3 * i + 1] = 1 + (i + 1) % m_mesh;
				ibo_ptr[3 * i + 2] = 1 + (i + 0) % m_mesh;
			}
			//face +x3
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				ibo_ptr[3 * m_mesh + 3 * i + 0] = m_mesh + 1;
				ibo_ptr[3 * m_mesh + 3 * i + 1] = m_mesh + 2 + (i + 0) % m_mesh;
				ibo_ptr[3 * m_mesh + 3 * i + 2] = m_mesh + 2 + (i + 1) % m_mesh;
			}
			//edges
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				ibo_ptr[6 * m_mesh + 6 * i + 0] = 0 * (m_mesh + 1) + (i + 0) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 1] = 0 * (m_mesh + 1) + (i + 1) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 2] = 1 * (m_mesh + 1) + (i + 1) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 3] = 0 * (m_mesh + 1) + (i + 0) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 4] = 1 * (m_mesh + 1) + (i + 1) % m_mesh + 1;
				ibo_ptr[6 * m_mesh + 6 * i + 5] = 1 * (m_mesh + 1) + (i + 0) % m_mesh + 1;
			}
		}
		void Cylinder::vbo_edges_data(vertices::Model3D* vbo_ptr) const
		{
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				const float t = 2 * float(M_PI) * i / m_mesh;
				(vbo_ptr + 0 * m_mesh + i)->m_color = m_color_stroke;
				(vbo_ptr + 1 * m_mesh + i)->m_color = m_color_stroke;
				(vbo_ptr + 0 * m_mesh + i)->m_position = m_model_matrix * vec3(cosf(t), sinf(t), -0.5f);
				(vbo_ptr + 1 * m_mesh + i)->m_position = m_model_matrix * vec3(cosf(t), sinf(t), +0.5f);
			}
		}
		void Cylinder::vbo_faces_data(vertices::Model3D* vbo_ptr) const
		{
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				const float t = 2 * float(M_PI) * i / m_mesh;
				vbo_ptr[0 * (m_mesh + 1) + i + 1].m_color = m_color_fill;
				vbo_ptr[1 * (m_mesh + 1) + i + 1].m_color = m_color_fill;
				vbo_ptr[0 * (m_mesh + 1) + i + 1].m_position = m_model_matrix * vec3(cosf(t), sinf(t), -0.5f);
				vbo_ptr[1 * (m_mesh + 1) + i + 1].m_position = m_model_matrix * vec3(cosf(t), sinf(t), +0.5f);
			}
			vbo_ptr[0 * (m_mesh + 1)].m_color = m_color_fill;
			vbo_ptr[1 * (m_mesh + 1)].m_color = m_color_fill;
			vbo_ptr[0 * (m_mesh + 1)].m_position = m_model_matrix * vec3({0.0f, 0.0f, -0.5});
			vbo_ptr[1 * (m_mesh + 1)].m_position = m_model_matrix * vec3({0.0f, 0.0f, +0.5});
		}

		//buffers
		void Cylinder::setup(void)
		{
			//allocate
			m_ibo.allocate(18 * m_mesh);
			m_vbo.allocate(4 * m_mesh + 2);
			uint32_t* ibo_data = m_ibo.data();
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//vbo data
			vbo_faces_data(vbo_ptr);
			vbo_edges_data(vbo_ptr + 2 * (m_mesh + 1));
			//ibo data
			ibo_faces_data(ibo_data);
			ibo_edges_data(ibo_data + 12 * m_mesh);
			//transfer
			m_ibo.transfer();
			m_vbo.transfer();
		}
		void Cylinder::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawElements(GL_TRIANGLES, 12 * m_mesh, GL_UNSIGNED_INT, nullptr);
			glDrawElementsBaseVertex(GL_LINES, 6 * m_mesh, GL_UNSIGNED_INT, (void*) (12 * m_mesh * sizeof(uint32_t)), 2 * (m_mesh + 1));
		}

		//static
		uint32_t Cylinder::m_mesh = 60;
	}
}