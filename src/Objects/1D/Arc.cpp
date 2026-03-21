//std
#include <cmath>

//canvas
#include "Canvas/inc/Objects/1D/Arc.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Arc::Arc(void)
		{
			return;
		}

		//destructor
		Arc::~Arc(void)
		{
			return;
		}

		//data
		float Arc::angle(void) const
		{
			return m_angle;
		}
		float Arc::angle(float angle)
		{
			return m_angle = angle;
		}

		uint32_t Arc::mesh(void)
		{
			return m_mesh;
		}
		uint32_t Arc::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		//draw
		void Arc::draw(void)
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_LINE_STRIP, 0, m_mesh + 1);
		}
		void Arc::setup(void)
		{
			m_vbo.allocate(m_mesh + 1);
		}
		void Arc::update(void)
		{
			//data
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//vbo data
			for(uint32_t i = 0; i <= m_mesh; i++)
			{
				//data
				const float t = m_angle * i / m_mesh;
				//vertex
				vbo_ptr[i].m_color = m_color_stroke;
				vbo_ptr[i].m_position = vec3(cosf(t), sinf(t), 0);
			}
			//transfer
			apply_model();
			m_vbo.transfer();
		}

		//static
		uint32_t Arc::m_mesh = 60;
	}
}