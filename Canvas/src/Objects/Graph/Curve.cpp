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
				m_line{true}, m_line_color{"white"}, m_line_width{1}, 
				m_point{true}, m_point_color{"white"}, m_point_size{5}, m_point_type{1},
				m_shader{"Curve2D"}, m_frame{nullptr}
			{
				return;
			}

			//destructor
			Curve::~Curve(void)
			{
				return;
			}

			//data
			bool Curve::line(void) const
			{
				return m_line;
			}
			bool Curve::line(bool line)
			{
				return m_line = line;
			}

			Color Curve::line_color(void) const
			{
				return m_line_color;
			}
			Color Curve::line_color(const Color& line_color)
			{
				return m_line_color = line_color;
			}

			uint32_t Curve::line_width(void) const
			{
				return m_line_width;
			}
			uint32_t Curve::line_width(uint32_t thickness)
			{
				return m_line_width = thickness;
			}

			bool Curve::point(void) const
			{
				return m_point;
			}
			bool Curve::point(bool point)
			{
				return m_point = point;
			}

			Color Curve::point_color(void) const
			{
				return m_point_color;
			}
			Color Curve::point_color(const Color& point_color)
			{
				return m_point_color = point_color;
			}

			uint32_t Curve::point_size(void) const
			{
				return m_point_size;
			}
			uint32_t Curve::point_size(uint32_t point_size)
			{
				return m_point_size = point_size;
			}

			uint32_t Curve::point_type(void) const
			{
				return m_point_type;
			}
			uint32_t Curve::point_type(uint32_t point_type)
			{
				return m_point_type = point_type;
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
				m_ssbo.transfer(0 * sf, 4 * sf, m_line_color.channels());
				m_ssbo.transfer(4 * sf + 1 * si, 1 * sf, &m_line_width);
				for(uint32_t i = 0; i < np; i++)
				{
					const vec2 np = m_frame->ndc(m_data[i]);
					m_ssbo.transfer((5 + 2 * i) * sf + si, 2 * sf, np.data());
				}
			}
			void Curve::draw(void) const
			{
				m_vao.bind();
				m_shader.bind();
				m_ssbo.bind_base(0);
				glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, m_data.size() - 1);
			}
		}
	}
}