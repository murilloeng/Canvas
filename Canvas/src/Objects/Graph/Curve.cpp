//Canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Curve.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Frame.hpp"

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
			void Curve::setup(void)
			{
				//data
				const uint32_t np = m_data.size();
				const uint64_t si = sizeof(GLuint);
				const uint64_t sf = sizeof(GLfloat);
				m_ssbo.allocate(2 * si + 2 * np * sf);
				//ubos data
				m_ubo_lines.transfer(0, sizeof(m_lines), &m_lines);
				m_ubo_points.transfer(0, sizeof(m_points), &m_points);
				//ssbo data
				m_ssbo.transfer(0, 1 * si, &np);
				for(uint32_t i = 0; i < np; i++)
				{
					const vec2 np = m_frame->ndc(m_data[i]);
					m_ssbo.transfer(2 * si + 2 * i * sf, 2 * sf, np.data());
				}
			}
			void Curve::draw(void) const
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
		}
	}
}