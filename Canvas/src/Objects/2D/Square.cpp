//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Square.hpp"

//static data
static const float positions[] = {
	-1.0f, -1.0f, +0.0f,
	+1.0f, -1.0f, +0.0f,
	+1.0f, +1.0f, +0.0f,
	-1.0f, +1.0f, +0.0f
};

namespace canvas
{
	namespace objects
	{
		//constructors
		Square::Square(void) : m_color_fill{"blue"}, m_color_stroke{"white"}
		{
			m_vbo.allocate(8);
		}

		//destructor
		Square::~Square(void)
		{
			return;
		}

		//data
		Color Square::color_fill(void) const
		{
			return m_color_fill;
		}
		Color Square::color_fill(const Color& color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color Square::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color Square::color_stroke(const Color& color_stroke)
		{
			return m_color_stroke = color_stroke;
		}

		//draw
		void Square::setup(void)
		{
			//data
			vertices::Model3D* vbo_data = (vertices::Model3D*) m_vbo.data();
			//vbo data
			for(uint32_t i = 0; i < 4; i++)
			{
				vbo_data[i + 0].m_color = m_color_fill;
				vbo_data[i + 4].m_color = m_color_stroke;
				vbo_data[i + 0].m_position = m_model_matrix * vec3(positions + 3 * i);
				vbo_data[i + 4].m_position = m_model_matrix * vec3(positions + 3 * i);
			}
			m_vbo.transfer();
		}
		void Square::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_LINE_LOOP, 4, 4);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		}
	}
}