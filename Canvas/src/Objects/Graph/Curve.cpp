//Canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			//constructor
			Curve::Curve(void) : 
				m_color{"white"}, m_thickness{10}, 
				m_shader{{new shaders::Stage(GL_VERTEX_SHADER, "Line.vert"), new shaders::Stage(GL_FRAGMENT_SHADER, "Line.frag")}}
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
			}

			//destructor
			Curve::~Curve(void)
			{
				return;
			}

			//data
			Color Curve::color(void) const
			{
				return m_color;
			}
			Color Curve::color(const Color& color)
			{
				return m_color = color;
			}

			float Curve::thickness(void) const
			{
				return m_thickness;
			}
			float Curve::thickness(float thickness)
			{
				return m_thickness = thickness;
			}

			std::vector<vec3>& Curve::points(void)
			{
				return m_points;
			}
			const std::vector<vec3>& Curve::points(void) const
			{
				return m_points;
			}

			//draw
			void Curve::setup(void)
			{
				//data
				const uint32_t np = m_points.size();
				//vbo data
				m_vbo.allocate(np - 1);
				float* vbo_ptr = (float*) m_vbo.data();
				for(uint32_t i = 0; i + 1 < np; i++)
				{
					vbo_ptr[11 * i + 6] = m_color[0];
					vbo_ptr[11 * i + 7] = m_color[1];
					vbo_ptr[11 * i + 8] = m_color[2];
					vbo_ptr[11 * i + 9] = m_color[3];
					vbo_ptr[11 * i +10] = m_thickness;
					vbo_ptr[11 * i + 0] = m_points[i + 0][0];
					vbo_ptr[11 * i + 1] = m_points[i + 0][1];
					vbo_ptr[11 * i + 2] = m_points[i + 0][2];
					vbo_ptr[11 * i + 3] = m_points[i + 1][0];
					vbo_ptr[11 * i + 4] = m_points[i + 1][1];
					vbo_ptr[11 * i + 5] = m_points[i + 1][2];
				}
				//transfer
				m_vbo.transfer();
			}
			void Curve::draw(void) const
			{
				m_vao.bind();
				m_shader.bind();
				const uint32_t np = m_points.size();
				glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, np - 1);
			}
		}
	}
}