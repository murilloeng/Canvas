//Canvas
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Bezier.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Bezier::Bezier(void) : m_type{Type::Conic}
		{
			return;
		}

		//destructor
		Bezier::~Bezier(void)
		{
			return;
		}

		//data
		uint32_t Bezier::mesh(void)
		{
			return m_mesh;
		}
		uint32_t Bezier::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		Bezier::Type Bezier::type(Type type)
		{
			return m_type = type;
		}
		Bezier::Type Bezier::type(void) const
		{
			return m_type;
		}

		vec3 Bezier::point(uint32_t index) const
		{
			return m_points[index];
		}
		vec3 Bezier::point(uint32_t index, vec3 point)
		{
			return m_points[index] = point;
		}

		vec3 Bezier::control(uint32_t index) const
		{
			return m_controls[index];
		}
		vec3 Bezier::control(uint32_t index, vec3 control)
		{
			return m_controls[index] = control;
		}

		//draw
		void Bezier::setup(void)
		{
			//allocate
			m_vbo.allocate(m_mesh + 1);
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//vbo data
			const vec3& x1 = m_points[0];
			const vec3& x2 = m_points[1];
			const vec3& c1 = m_controls[0];
			const vec3& c2 = m_controls[1];
			for(uint32_t i = 0; i <= m_mesh; i++)
			{
				const float t = float(i) / m_mesh;
				vbo_ptr[i].m_color = m_color_stroke;
				if(m_type == Type::Conic)
				{
					const float s = 1 - t;
					vbo_ptr[i].m_position = s * s * x1 + 2 * s * t * c1 + t * t * x2;
				}
				else
				{
					const float s = 1 - t;
					vbo_ptr[i].m_position = s * s * s * x1 + 3 * s * s * t * c1 + 3 * s * t * t * c2 + t * t * t * x2;
				}
			}
			//transfer
			m_vbo.transfer();
		}
		void Bezier::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_LINE_STRIP, 0, m_mesh + 1);
		}

		//static
		uint32_t Bezier::m_mesh = 60;
	}
}
