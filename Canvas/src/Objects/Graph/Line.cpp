//Canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Line.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			//constructor
			Line::Line(void) : 
				m_color{"white"}, m_points{{0, 0, 0}, {1, 0, 0}},  m_thickness{10}, 
				m_shader{{new shaders::Stage(GL_VERTEX_SHADER, "line.vert"), new shaders::Stage(GL_FRAGMENT_SHADER, "line.frag")}}
			{
				//vbo setup
				m_vbo.vertex_size(11 * sizeof(float));
				//vao setup
				m_vao.attribute_enable(0);
				m_vao.attribute_enable(1);
				m_vao.attribute_enable(2);
				m_vao.attribute_enable(3);
				m_vao.binding_divisor(0, 1);
				m_vao.attribute_binding(0, 0);
				m_vao.attribute_binding(1, 0);
				m_vao.attribute_binding(2, 0);
				m_vao.attribute_binding(3, 0);
				m_vao.vertex_buffer(0, m_vbo.id(), 0, 11 * sizeof(float));
				m_vao.attribute_format(0, 3, GL_FLOAT,  0 * sizeof(float));
				m_vao.attribute_format(1, 3, GL_FLOAT,  3 * sizeof(float));
				m_vao.attribute_format(2, 4, GL_FLOAT,  6 * sizeof(float));
				m_vao.attribute_format(3, 1, GL_FLOAT, 10 * sizeof(float));
				//allocate
				m_vbo.allocate(1);
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

			float Line::thickness(void) const
			{
				return m_thickness;
			}
			float Line::thickness(float thickness)
			{
				return m_thickness = thickness;
			}

			vec3 Line::point(uint32_t index) const
			{
				return m_points[index];
			}
			vec3 Line::point(uint32_t index, const vec3& point)
			{
				return m_points[index] = point;
			}

			//draw
			void Line::setup(void)
			{
				//data
				float* vbo_ptr = (float*) m_vbo.data();
				//vbo data
				vbo_ptr[ 6] = m_color[0];
				vbo_ptr[ 7] = m_color[1];
				vbo_ptr[ 8] = m_color[2];
				vbo_ptr[ 9] = m_color[3];
				vbo_ptr[10] = m_thickness;
				vbo_ptr[ 0] = m_points[0][0];
				vbo_ptr[ 1] = m_points[0][1];
				vbo_ptr[ 2] = m_points[0][2];
				vbo_ptr[ 3] = m_points[1][0];
				vbo_ptr[ 4] = m_points[1][1];
				vbo_ptr[ 5] = m_points[1][2];
				//transfer
				m_vbo.transfer();
			}
			void Line::draw(void) const
			{
				m_vao.bind();
				m_shader.bind();
				glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 1);
			}
		}
	}
}