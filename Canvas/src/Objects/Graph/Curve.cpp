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
			Curve::Curve(void) : m_color{"white"}, m_thickness{1}, m_shader{"Curve2D"}, m_frame{nullptr}
			{
				return;
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

			std::vector<vec2>& Curve::points(void)
			{
				return m_points;
			}
			const std::vector<vec2>& Curve::points(void) const
			{
				return m_points;
			}

			//draw
			void Curve::setup(void)
			{
				//data
				const uint64_t si = sizeof(GLuint);
				const uint64_t sf = sizeof(GLfloat);
				const uint32_t np = m_points.size();
				m_ssbo.allocate((5 + 2 * np) * sf + si);
				//ssbo data
				m_ssbo.transfer(4 * sf, 1 * si, &np);
				m_ssbo.transfer(0 * sf, 4 * sf, m_color.channels());
				m_ssbo.transfer(4 * sf + 1 * si, 1 * sf, &m_thickness);
				for(uint32_t i = 0; i < np; i++)
				{
					m_ssbo.transfer((5 + 2 * i) * sf + si, 2 * sf, m_points[i].data());
				}
			}
			void Curve::draw(void) const
			{
				m_vao.bind();
				m_shader.bind();
				m_ssbo.bind_base(0);
				glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, m_points.size() - 1);
			}
		}
	}
}