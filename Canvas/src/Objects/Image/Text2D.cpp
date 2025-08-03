//std
#include <cmath>
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Fonts/Font.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"

#include "Canvas/Canvas/inc/Objects/Image/Text2D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Text2D::Text2D(void) : 
			m_size{1.0f}, m_angle{0}, m_font{0}, m_position{0, 0}, m_line_spacing{0.2f}
		{
			return;
		}

		//destructor
		Text2D::~Text2D(void)
		{
			return;
		}

		//data
		float Text2D::size(void) const
		{
			return m_size;
		}
		float Text2D::size(float size)
		{
			return m_size = size;
		}

		float Text2D::angle(void) const
		{
			return m_angle;
		}
		float Text2D::angle(float angle)
		{
			return m_angle = angle;
		}

		uint32_t Text2D::font(void) const
		{
			return m_font;
		}
		uint32_t Text2D::font(uint32_t font)
		{
			return m_font = font;
		}

		Anchor Text2D::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Text2D::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		vec2 Text2D::position(void) const
		{
			return m_position;
		}
		vec2 Text2D::position(const vec2& position)
		{
			return m_position = position;
		}

		std::string Text2D::string(void) const
		{
			return m_string;
		}
		std::string Text2D::string(std::string text)
		{
			return m_string = text;
		}

		float Text2D::line_spacing(void) const
		{
			return m_line_spacing;
		}
		float Text2D::line_spacing(float line_spacing)
		{
			return m_line_spacing = m_line_spacing;
		}

		//text
		uint32_t Text2D::width(void) const
		{
			uint32_t w = 0;
			uint32_t v = 0;
			for(char c : m_string)
			{
				if(c == '\n')
				{
					w = std::max(w, v), v = 0;
				}
				else
				{
					v += m_scene->font(m_font)->glyph(c).advance();
				}
			}
			return std::max(w, v);
		}
		uint32_t Text2D::height(void) const
		{
			//data
			uint32_t h = 0, a = 0, b = 0;
			fonts::Font *font = m_scene->font(m_font);
			//height
			for(char c : m_string)
			{
				if(c == '\n' || c == '\v')
				{
					h += a + b + uint32_t(m_line_spacing) * font->height(), a = b = 0;
				}
				else
				{
					a = std::max(a, font->glyph(c).bearing(1));
					b = std::max(b, font->glyph(c).height() - font->glyph(c).bearing(1));
				}
			}
			return h + a + b;
		}
		uint32_t Text2D::length(void) const
		{
			uint32_t v = 0;
			for(char c : m_string)
			{
				if(c >= 32) v++;
			}
			return v;
		}

		//setup
		void Text2D::setup(void)
		{
			//check
			uint32_t a = 0, b = 0;
			// if(m_font >= m_scene->fonts().size())
			// {
			// 	throw std::runtime_error("Error: Text object font has out of range index!");
			// }
			//lines
			for(char c : m_string)
			{
				if(c == '\n' || c == '\v')
				{
					m_lines.push_back(a), m_lines.push_back(b), a = b = 0;
				}
				else
				{
					const fonts::Font *font = m_scene->font(m_font);
					a = std::max(a, font->glyph(c).bearing(1));
					b = std::max(b, font->glyph(c).height() - font->glyph(c).bearing(1));
				}
			}
			m_lines.push_back(a), m_lines.push_back(b);
			//indexes
			Object::setup();
		}

		//data
		void Text2D::vbo_fill_data(void) const
		{
			//data
			uint32_t line = 0;
			const uint32_t wt = width();
			const uint32_t ht = height();
			float xa[2], xs[2], xc[8], tc[8];
			const vec3 up = m_scene->camera().up();
			const vec3 ur = m_scene->camera().right();
			const fonts::Font *font = m_scene->font(m_font);
			const float ps = m_size / font->height();
			const vec2 t1(+cosf(m_angle), +sinf(m_angle));
			const vec2 t2(-sinf(m_angle), +cosf(m_angle));
			vertices::Text2D* vbo_ptr = vbo_data_text_2D();
			//anchor
			xs[0] = xs[1] = 0;
			xa[0] = -ps * wt * m_anchor.horizontal() / 2;
			xa[1] = -ps * m_lines[0] + ps * ht * (2 - m_anchor.vertical()) / 2;
			//vbo data
			for(uint32_t i = 0; i < m_string.length(); i++)
			{
				if(m_string[i] >= 32)
				{
					//character
					font->glyph(m_string[i]).coordinates(tc);
					const int32_t w = font->glyph(m_string[i]).width();
					const int32_t h = font->glyph(m_string[i]).height();
					const int32_t r = font->glyph(m_string[i]).advance();
					const int32_t a = font->glyph(m_string[i]).bearing(0);
					const int32_t b = font->glyph(m_string[i]).bearing(1);
					//position
					xc[2 * 0 + 0] = xc[2 * 3 + 0] = xa[0] + xs[0] + ps * a;
					xc[2 * 2 + 1] = xc[2 * 3 + 1] = xa[1] + xs[1] + ps * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = xa[0] + xs[0] + ps * (a + w);
					xc[2 * 0 + 1] = xc[2 * 1 + 1] = xa[1] + xs[1] + ps * (b - h);
					//vertices
					for(uint32_t j = 0; j < 4; j++)
					{
						vbo_ptr[j].m_color = m_color_fill;
						vbo_ptr[j].m_texture_coordinates = tc + 2 * j;
						vbo_ptr[j].m_position = m_position + xc[2 * j + 0] * t1 + xc[2 * j + 1] * t2;
					}
					vbo_ptr += 4;
					xs[0] += ps * r;
				}
				if(m_string[i] == '\t')
				{
					xs[0] += 4 * ps * font->glyph(' ').advance();
				}
				if(m_string[i] == '\n')
				{
					xs[0] = 0;
					xs[1] -= ps * (m_lines[2 * line + 1] + m_lines[2 * line + 2] + m_line_spacing * font->height());
				}
				if(m_string[i] == '\v')
				{
					xs[1] -= ps * (m_lines[2 * line + 1] + m_lines[2 * line + 2] + m_line_spacing * font->height());
				}
			}
		}
		void Text2D::ibo_fill_data(void) const
		{
			//data
			const uint32_t s = length();
			uint32_t* ibo_ptr = ibo_data(10);
			//ibo data
			for(uint32_t i = 0; i < s; i++)
			{
				ibo_ptr[6 * i + 0] = m_vbo_index[5] + 4 * i + 0;
				ibo_ptr[6 * i + 1] = m_vbo_index[5] + 4 * i + 1;
				ibo_ptr[6 * i + 2] = m_vbo_index[5] + 4 * i + 2;
				ibo_ptr[6 * i + 3] = m_vbo_index[5] + 4 * i + 0;
				ibo_ptr[6 * i + 4] = m_vbo_index[5] + 4 * i + 2;
				ibo_ptr[6 * i + 5] = m_vbo_index[5] + 4 * i + 3;
			}
		}

		//buffers
		void Text2D::buffers_size(void)
		{
			m_vbo_size[ 5] = 4 * m_fill * length();
			m_ibo_size[10] = 6 * m_fill * length();
		}
		void Text2D::buffers_data(void) const
		{
			if(m_fill) vbo_fill_data();
			if(m_fill) ibo_fill_data();
		}
	}
}