//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Circle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Circle::Circle(void)
		{
			return;
		}

		//destructor
		Circle::~Circle(void)
		{
			return;
		}

		//data
		uint32_t Circle::mesh(void)
		{
			return m_mesh;
		}
		uint32_t Circle::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		//draw
		void Circle::setup(void)
		{
			//allocate
			m_vbo.allocate(2 * m_mesh);
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//vbo data
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				//data
				const float t = 2 * float(M_PI) * i / m_mesh;
				//colors
				vbo_ptr[i].m_color = m_color_fill;
				vbo_ptr[i + m_mesh].m_color = m_color_stroke;
				//positions
				vbo_ptr[i].m_position = m_model_matrix * vec3({cosf(t), sinf(t), 0});
				vbo_ptr[i + m_mesh].m_position = m_model_matrix * vec3({cosf(t), sinf(t), 0});
			}
			//transfer
			m_vbo.transfer();
		}
		void Circle::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_TRIANGLE_FAN, 0, m_mesh);
			glDrawArrays(GL_LINE_LOOP, m_mesh, m_mesh);
		}

		//static
		uint32_t Circle::m_mesh = 60;
	}
}