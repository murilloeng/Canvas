//Canvas
#include "Canvas/inc/API/API.hpp"
#include "Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/inc/Objects/Graph/Curve.hpp"
#include "Canvas/inc/Objects/Graph/Frame.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			//constructor
			Curve::Curve(void) : m_frame{nullptr}, m_shader_lines{"Graph2D-Lines"}, m_shader_points{"Graph2D-Points"}
			{
				m_ubo_lines.allocate(sizeof(Lines));
				m_ubo_points.allocate(sizeof(Points));
			}

			//destructor
			Curve::~Curve(void)
			{
				return;
			}

			//data
			Lines& Curve::lines(void)
			{
				return m_lines;
			}
			Points& Curve::points(void)
			{
				return m_points;
			}

			std::vector<vec2>& Curve::data(void)
			{
				return m_data;
			}
			const std::vector<vec2>& Curve::data(void) const
			{
				return m_data;
			}

			//draw
			void Curve::draw(void)
			{
				//lines
				m_vao.bind();
				m_ssbo.bind_base(0);
				if(m_lines.enabled())
				{
					m_shader_lines.bind();
					m_ubo_lines.bind_base(2);
					glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, m_data.size() - 1);
				}
				//points
				if(m_points.enabled())
				{
					m_shader_points.bind();
					m_ubo_points.bind_base(2);
					glDrawArraysInstanced(GL_POINTS, 0, 1, m_data.size() / m_points.skip());
				}
			}
			void Curve::setup(void)
			{
				const uint32_t np = m_data.size();
				const uint64_t si = sizeof(GLuint);
				const uint64_t sf = sizeof(GLfloat);
				m_ssbo.allocate(4 * si + 4 * sf * np);
			}
			void Curve::update(void)
			{
				//data
				const uint32_t np = m_data.size();
				const uint64_t si = sizeof(GLuint);
				const uint64_t sf = sizeof(GLfloat);
				//ubos data
				m_ubo_lines.transfer(0, sizeof(m_lines), &m_lines);
				m_ubo_points.transfer(0, sizeof(m_points), &m_points);
				//ssbo data
				float length = 0;
				m_ssbo.transfer(0, si, &np);
				for(uint32_t i = 0; i < np; i++)
				{
					const vec2 ndc = m_frame->ndc(m_data[i]);
					m_ssbo.transfer(4 * si + 4 * i * sf, 2 * sf, ndc.data());
					m_ssbo.transfer(4 * si + 4 * i * sf + 2 * sf, sf, &length);
					if(i + 1 != np) length += (m_frame->pixel(m_data[i + 1]) - m_frame->pixel(m_data[i])).norm();
				}
			}
		}
	}
}