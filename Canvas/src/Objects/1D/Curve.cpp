//canvas
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Curve::Curve(void) : m_domain{0, 1}
		{
			return;
		}

		//destructor
		Curve::~Curve(void)
		{
			return;
		}

		//data
		uint32_t Curve::mesh(void) const
		{
			return m_mesh;
		}
		uint32_t Curve::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		float Curve::domain(uint32_t index) const
		{
			return m_domain[index];
		}
		float Curve::domain(uint32_t index, float domain)
		{
			return m_domain[index] = domain;
		}

		std::function<vec3(float)> Curve::position(void) const
		{
			return m_position;
		}
		std::function<vec3(float)> Curve::position(std::function<vec3(float)> position)
		{
			return m_position = position;
		}

		//draw
		void Curve::setup(void)
		{
			//allocate
			m_vbo.allocate(m_mesh + 1);
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//vbo data
			const float a = m_domain[0];
			const float b = m_domain[1];
			for(uint32_t i = 0; i <= m_mesh; i++)
			{
				//data
				const float t = a + (b - a) * i / m_mesh;
				//vertex
				vbo_ptr[i].m_color = m_color_stroke;
				vbo_ptr[i].m_position = m_position(t);
			}
			//transfer
			m_vbo.transfer();
		}
		void Curve::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_LINE_STRIP, 0, m_mesh + 1);
		}
	}
}