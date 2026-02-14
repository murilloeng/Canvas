//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/0D/Point.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Point::Point(void) : m_color{"blue"}, m_position{0, 0, 0}
		{
			//data
			m_vao = new buffers::VAO;
			m_vbo = new buffers::VBO(false);
			m_shader = new shaders::Shader({
				new shaders::Stage(GL_VERTEX_SHADER, "Canvas/shd/model3D.vert"),
				new shaders::Stage(GL_FRAGMENT_SHADER, "Canvas/shd/model3D.frag")
			});
			//vao setup
			m_vao->attribute_enable(0);
			m_vao->attribute_enable(1);
			m_vao->attribute_binding(0, 0);
			m_vao->attribute_binding(1, 0);
			m_vao->attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
			m_vao->attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
			m_vao->vertex_buffer(0, m_vbo->id(), 0, sizeof(vertices::Model3D));
			//vbo setup
			m_vbo->vertex_count(1);
			m_vbo->vertex_size(sizeof(vertices::Model3D));
		}

		//destructor
		Point::~Point(void)
		{
			delete m_vao;
			delete m_vbo;
		}

		//data
		Color Point::color(void) const
		{
			return m_color;
		}
		Color Point::color(const Color& color)
		{
			return m_color;
		}

		vec3 Point::position(void) const
		{
			return m_position;
		}
		vec3 Point::position(const vec3& position)
		{
			return m_position = position;
		}

		//draw
		void Point::setup(void)
		{
			//data
			m_vbo->allocate();
			vertices::Model3D* vertex = (vertices::Model3D*) m_vbo->data();
			//vbo data
			vertex->m_color = m_color;
			vertex->m_position = m_position;
			//vbo transfer
			m_vbo->transfer();
		}
		void Point::draw(void) const
		{
			m_vao->bind();
			m_shader->bind();
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}
}