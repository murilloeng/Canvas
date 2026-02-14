//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Triangle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Triangle::Triangle(void) : 
			m_color{"white"}, 
			m_positions{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}}, 
			m_shader({
				new shaders::Stage(GL_VERTEX_SHADER, "model3D.vert"),
				new shaders::Stage(GL_FRAGMENT_SHADER, "model3D.frag")
			})
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
			m_vbo.vertex_count(3);
			m_vbo.vertex_size(sizeof(vertices::Model3D));
			//allocate
			m_vbo.allocate();
		}

		//destructor
		Triangle::~Triangle(void)
		{
			return;
		}

		//data
		Color Triangle::color(void) const
		{
			return m_color;
		}
		Color Triangle::color(const Color& color)
		{
			return m_color;
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
				vbo_data[i].m_color = m_color;
				vbo_data[i].m_position = m_model_matrix * m_positions[i];
			}
			//transfer
			m_vbo.transfer();
		}
		void Triangle::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
}