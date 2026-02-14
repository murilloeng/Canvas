//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Line::Line(void) : 
			m_color("white"), 
			m_positions{{0, 0, 0}, {1, 0, 0}}, 
			m_shader{{
				new shaders::Stage(GL_VERTEX_SHADER, "model3D.vert"),
				new shaders::Stage(GL_FRAGMENT_SHADER, "model3D.frag")
			}}
		{
			//vao setup
			m_vao.attribute_enable(0);
			m_vao.attribute_enable(1);
			m_vao.attribute_binding(0, 0);
			m_vao.attribute_binding(1, 0);
			m_vao.attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
			m_vao.attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
			m_vao.vertex_buffer(0, m_vbo.id(), 0, sizeof(vertices::Model3D));
			//vbo setup
			m_vbo.vertex_count(2);
			m_vbo.vertex_size(sizeof(vertices::Model3D));
			//allocate
			m_vbo.allocate();
		}

		//destructor
		Line::~Line(void)
		{
			return;
		}

		//data
		Color Line::color(void) const
		{
			return m_color;
		}
		Color Line::color(const Color& color)
		{
			return m_color = color;
		}

		vec3 Line::position(uint32_t index) const
		{
			return m_positions[index];
		}
		vec3 Line::position(uint32_t index, const vec3& point)
		{
			return m_positions[index] = point;
		}

		//draw
		void Line::setup(void)
		{
			//data
			vertices::Model3D* vbo_data = (vertices::Model3D*) m_vbo.data();
			//colors
			vbo_data[0].m_color = m_color;
			vbo_data[1].m_color = m_color;
			//positions
			vbo_data[0].m_position = m_positions[0];
			vbo_data[1].m_position = m_positions[1];
			//transfer
			m_vbo.transfer();
		}
		void Line::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_LINES, 0, 2);
		}
	}
}