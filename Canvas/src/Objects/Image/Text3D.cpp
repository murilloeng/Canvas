//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Fonts/Font.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"

#include "Canvas/Canvas/inc/Objects/Image/Text3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Text3D::Text3D(void) : 
			m_size(1.0f), m_normal(false), m_font(0), m_position{0, 0, 0}, 
			m_directions{{1, 0, 0}, {0, 1, 0}}, m_line_spacing(0.2f)
		{
			return;
		}

		//destructor
		Text3D::~Text3D(void)
		{
			return;
		}

		//data
		float Text3D::size(void) const
		{
			return m_size;
		}
		float Text3D::size(float size)
		{
			return m_size = size;
		}

		bool Text3D::normal(void) const
		{
			return m_normal;
		}
		bool Text3D::normal(bool normal)
		{
			return m_normal = normal;
		}

		uint32_t Text3D::font(void) const
		{
			return m_font;
		}
		uint32_t Text3D::font(uint32_t font)
		{
			return m_font = font;
		}

		Anchor Text3D::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Text3D::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		vec3 Text3D::position(void) const
		{
			return m_position;
		}
		vec3 Text3D::position(const vec3& position)
		{
			return m_position = position;
		}

		std::string Text3D::text(void) const
		{
			return m_text;
		}
		std::string Text3D::text(std::string text)
		{
			return m_text = text;
		}

		float Text3D::line_spacing(void) const
		{
			return m_line_spacing;
		}
		float Text3D::line_spacing(float line_spacing)
		{
			return m_line_spacing = m_line_spacing;
		}

		vec3 Text3D::direction(uint32_t index) const
		{
			return m_directions[index];
		}
		vec3 Text3D::direction(uint32_t index, const vec3 &direction)
		{
			return m_directions[index] = direction;
		}

		//text
		uint32_t Text3D::width(void) const
		{
			uint32_t w = 0;
			uint32_t v = 0;
			for(char c : m_text)
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
		uint32_t Text3D::height(void) const
		{
			//data
			uint32_t h = 0, a = 0, b = 0;
			fonts::Font *font = m_scene->font(m_font);
			//height
			for(char c : m_text)
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
		uint32_t Text3D::length(void) const
		{
			uint32_t v = 0;
			for(char c : m_text)
			{
				if(c >= 32) v++;
			}
			return v;
		}

		//setup
		void Text3D::setup(void)
		{
			//check
			uint32_t a = 0, b = 0;
			if(m_font >= m_scene->fonts().size())
			{
				throw std::runtime_error("Error: Text object font has out of range index!");
			}
			//lines
			for(char c : m_text)
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
		void Text3D::vbo_fill_data(void) const
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
			vertices::Text3D* vbo_ptr = vbo_data_text_3D();
			const vec3 t1 = m_normal ? ur : m_directions[0];
			const vec3 t2 = m_normal ? up : m_directions[1];
			//anchor
			xs[0] = xs[1] = 0;
			xa[0] = -ps * wt * m_anchor.horizontal() / 2;
			xa[1] = -ps * m_lines[0] + ps * ht * (2 - m_anchor.vertical()) / 2;
			//vbo data
			for(uint32_t i = 0; i < m_text.length(); i++)
			{
				if(m_text[i] >= 32)
				{
					//character
					font->glyph(m_text[i]).coordinates(tc);
					const int32_t w = font->glyph(m_text[i]).width();
					const int32_t h = font->glyph(m_text[i]).height();
					const int32_t r = font->glyph(m_text[i]).advance();
					const int32_t a = font->glyph(m_text[i]).bearing(0);
					const int32_t b = font->glyph(m_text[i]).bearing(1);
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
				if(m_text[i] == '\t')
				{
					xs[0] += 4 * ps * font->glyph(' ').advance();
				}
				if(m_text[i] == '\n')
				{
					xs[0] = 0;
					xs[1] -= ps * (m_lines[2 * line + 1] + m_lines[2 * line + 2] + m_line_spacing * font->height());
				}
				if(m_text[i] == '\v')
				{
					xs[1] -= ps * (m_lines[2 * line + 1] + m_lines[2 * line + 2] + m_line_spacing * font->height());
				}
			}
		}
		void Text3D::ibo_fill_data(void) const
		{
			const uint32_t s = length();
			uint32_t* ibo_ptr = ibo_data(4);
			for(uint32_t i = 0; i < s; i++)
			{
				ibo_ptr[6 * i + 0] = m_vbo_index[2] + 4 * i + 0;
				ibo_ptr[6 * i + 1] = m_vbo_index[2] + 4 * i + 1;
				ibo_ptr[6 * i + 2] = m_vbo_index[2] + 4 * i + 2;
				ibo_ptr[6 * i + 3] = m_vbo_index[2] + 4 * i + 0;
				ibo_ptr[6 * i + 4] = m_vbo_index[2] + 4 * i + 2;
				ibo_ptr[6 * i + 5] = m_vbo_index[2] + 4 * i + 3;
			}
		}

		//buffers
		void Text3D::buffers_size(void)
		{
			m_vbo_size[2] = 4 * m_fill * length();
			m_ibo_size[4] = 6 * m_fill * length();
		}
		void Text3D::buffers_data(void) const
		{
			if(m_fill) vbo_fill_data();
			if(m_fill) ibo_fill_data();
		}

		//update
		void Text3D::update_on_motion(void) const
		{
			if(m_fill && m_normal) vbo_fill_data();
		}
	}
}