//Canvas
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Model3D::Model3D(void) : m_shader({
			new shaders::Stage(GL_VERTEX_SHADER, "model3D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, "model3D.frag")
		}), m_color_fill{"blue"}, m_color_stroke{"white"}
		{
			//vao setup
			m_vao.attribute_enable(0);
			m_vao.attribute_enable(1);
			m_vao.attribute_binding(0, 0);
			m_vao.attribute_binding(1, 0);
			m_vao.element_buffer(m_ibo.id());
			m_vao.attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
			m_vao.attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
			m_vao.vertex_buffer(0, m_vbo.id(), 0, sizeof(vertices::Model3D));
			//vbo setup
			m_vbo.vertex_size(sizeof(vertices::Model3D));
		}
		
		//destructor
		Model3D::~Model3D(void)
		{
			return;
		}

		//data
		Color Model3D::color_fill(void) const
		{
			return m_color_fill;
		}
		Color Model3D::color_fill(const Color& color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color Model3D::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color Model3D::color_stroke(const Color& color_stroke)
		{
			return m_color_stroke = color_stroke;
		}
	}
}