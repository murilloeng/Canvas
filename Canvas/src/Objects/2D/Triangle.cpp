//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Triangle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Triangle::Triangle(void) : m_positions{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}}, m_color_fill{"blue"}, m_color_stroke{"white"}
		{
			m_vbo.allocate(6);
		}

		//destructor
		Triangle::~Triangle(void)
		{
			return;
		}

		//data
		Color Triangle::color_fill(void) const
		{
			return m_color_fill;
		}
		Color Triangle::color_fill(const Color& color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color Triangle::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color Triangle::color_stroke(const Color& color_stroke)
		{
			return m_color_stroke = color_stroke;
		}

		vec3 Triangle::position(uint32_t index) const
		{
			return m_positions[index];
		}
		vec3 Triangle::position(uint32_t index, const vec3& position)
		{
			return m_positions[index] = position;
		}

		//draw
		void Triangle::setup(void)
		{
			//data
			vertices::Model3D* vbo_data = (vertices::Model3D*) m_vbo.data();
			//vbo data
			for(uint32_t i = 0; i < 3; i++)
			{
				vbo_data[i + 0].m_color = m_color_fill;
				vbo_data[i + 3].m_color = m_color_stroke;
				vbo_data[i + 0].m_position = m_model_matrix * m_positions[i];
				vbo_data[i + 3].m_position = m_model_matrix * m_positions[i];
			}
			//transfer
			m_vbo.transfer();
		}
		void Triangle::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawArrays(GL_LINE_LOOP, 3, 3);
		}
	}
}