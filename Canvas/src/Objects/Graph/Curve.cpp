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
			Curve::Curve(void) : 
				m_lines{true}, m_lines_color{"white"}, m_lines_width{1}, m_shader_lines{"Graph2D-Lines"}, 
				m_points{true}, m_points_color{"white"}, m_points_size{5}, m_points_skip{1}, m_points_type{1}, m_shader_points{"Graph2D-Points"},
				m_frame{nullptr}
			{
				return;
			}

			//destructor
			Curve::~Curve(void)
			{
				return;
			}

			//data
			bool Curve::lines(void) const
			{
				return m_lines;
			}
			bool Curve::lines(bool line)
			{
				return m_lines = line;
			}

			Color Curve::lines_color(void) const
			{
				return m_lines_color;
			}
			Color Curve::lines_color(const Color& lines_color)
			{
				return m_lines_color = lines_color;
			}

			uint32_t Curve::lines_width(void) const
			{
				return m_lines_width;
			}
			uint32_t Curve::lines_width(uint32_t lines_width)
			{
				return m_lines_width = lines_width;
			}

			bool Curve::points(void) const
			{
				return m_points;
			}
			bool Curve::points(bool points)
			{
				return m_points = points;
			}

			Color Curve::points_color(void) const
			{
				return m_points_color;
			}
			Color Curve::points_color(const Color& points_color)
			{
				return m_points_color = points_color;
			}

			uint32_t Curve::points_size(void) const
			{
				return m_points_size;
			}
			uint32_t Curve::points_size(uint32_t points_size)
			{
				return m_points_size = points_size;
			}

			uint32_t Curve::points_skip(void) const
			{
				return m_points_skip;
			}
			uint32_t Curve::points_skip(uint32_t points_skip)
			{
				return m_points_skip = points_skip;
			}

			uint32_t Curve::points_type(void) const
			{
				return m_points_type;
			}
			uint32_t Curve::points_type(uint32_t points_type)
			{
				return m_points_type = points_type;
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
				const uint64_t si = sizeof(GLuint);
				const uint64_t sf = sizeof(GLfloat);
				const uint32_t np = m_data.size();
				//allocate
				m_ssbo.allocate((5 + 2 * np) * sf + si);
				//ssbo data
				m_ssbo.transfer(4 * sf, 1 * si, &np);
				m_ssbo.transfer(0 * sf, 4 * sf, m_lines_color.channels());
				m_ssbo.transfer(4 * sf + 1 * si, 1 * sf, &m_lines_width);
				for(uint32_t i = 0; i < np; i++)
				{
					const vec2 np = m_frame->ndc(m_data[i]);
					m_ssbo.transfer((5 + 2 * i) * sf + si, 2 * sf, np.data());
				}
			}
			void Curve::draw(void) const
			{
				//lines
				if(m_lines)
				{
					m_vao.bind();
					m_shader_lines.bind();
					m_ssbo.bind_base(0);
					glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, m_data.size() - 1);
				}
				//points
				if(m_points)
				{
					m_vao.bind();
				}
			}
		}
	}
}