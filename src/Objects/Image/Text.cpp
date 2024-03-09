//canvas
#include "Canvas/inc/Scene/Font.hpp"
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/inc/Objects/Image/Text.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Text::Text(void) : m_size(1.0f), m_font(0), m_position{0, 0, 0}, m_directions{{1, 0, 0}, {0, 1, 0}}, m_line_spacing(0.2f)
		{
			return;
		}

		//destructor
		Text::~Text(void)
		{
			return;
		}

		//data
		float Text::size(void) const
		{
			return m_size;
		}
		float Text::size(float size)
		{
			return m_size = size;
		}

		unsigned Text::font(void) const
		{
			return m_font;
		}
		unsigned Text::font(unsigned font)
		{
			return m_font = font;
		}

		Anchor Text::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Text::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		vec3 Text::position(void) const
		{
			return m_position;
		}
		vec3 Text::position(const vec3 &position)
		{
			return m_position = position;
		}

		std::string Text::text(void) const
		{
			return m_text;
		}
		std::string Text::text(std::string text)
		{
			return m_text = text;
		}

		float Text::line_spacing(void) const
		{
			return m_line_spacing;
		}
		float Text::line_spacing(float line_spacing)
		{
			return m_line_spacing = m_line_spacing;
		}

		vec3 Text::direction(unsigned index) const
		{
			return m_directions[index];
		}
		vec3 Text::direction(unsigned index, const vec3 &direction)
		{
			return m_directions[index] = direction;
		}

		//text
		unsigned Text::width(void) const
		{
			unsigned w = 0;
			unsigned v = 0;
			for (char c : m_text)
			{
				if (c == '\n')
				{
					w = std::max(w, v), v = 0;
				}
				else
				{
					v += m_scene->font(m_font)->character(c).advance();
				}
			}
			return std::max(w, v);
		}
		unsigned Text::height(void) const
		{
			//data
			unsigned h = 0, a = 0, b = 0;
			Font *font = m_scene->font(m_font);
			//height
			for (char c : m_text)
			{
				if (c == '\n' || c == '\v')
				{
					h += a + b + unsigned(m_line_spacing) * font->height(), a = b = 0;
				}
				else
				{
					a = std::max(a, font->character(c).bearing(1));
					b = std::max(b, font->character(c).height() - font->character(c).bearing(1));
				}
			}
			return h + a + b;
		}
		unsigned Text::length(void) const
		{
			unsigned v = 0;
			for (char c : m_text)
			{
				if (c >= 32)
					v++;
			}
			return v;
		}

		//buffers
		unsigned Text::vbo_size(unsigned index) const
		{
			return 4 * m_fill * length() * (index == 2);
		}
		unsigned Text::ibo_size(unsigned index) const
		{
			return 2 * m_fill * length() * (index == 4);
		}

		//draw
		void Text::ibo_fill_data(unsigned **ibo_data) const
		{
			const unsigned s = length();
			for (unsigned i = 0; i < s; i++)
			{
				ibo_data[4][m_ibo_index[4] + 6 * i + 0] = m_vbo_index[2] + 4 * i + 0;
				ibo_data[4][m_ibo_index[4] + 6 * i + 1] = m_vbo_index[2] + 4 * i + 1;
				ibo_data[4][m_ibo_index[4] + 6 * i + 2] = m_vbo_index[2] + 4 * i + 2;
				ibo_data[4][m_ibo_index[4] + 6 * i + 3] = m_vbo_index[2] + 4 * i + 0;
				ibo_data[4][m_ibo_index[4] + 6 * i + 4] = m_vbo_index[2] + 4 * i + 2;
				ibo_data[4][m_ibo_index[4] + 6 * i + 5] = m_vbo_index[2] + 4 * i + 3;
			}
		}
		void Text::vbo_fill_data(vertices::Vertex **vbo_data) const
		{
			//data
			unsigned line = 0;
			const unsigned wt = width();
			const unsigned ht = height();
			float xa[2], xs[2], xc[8], tc[8];
			const vec3 &t1 = m_directions[0];
			const vec3 &t2 = m_directions[1];
			const Font *font = m_scene->font(m_font);
			const float ps = m_size / font->height();
			vertices::Text3D *vbo_ptr = (vertices::Text3D *)vbo_data[2] + m_vbo_index[2];
			//anchor
			xs[0] = xs[1] = 0;
			xa[0] = -ps * wt * m_anchor.horizontal() / 2;
			xa[1] = -ps * m_lines[0] + ps * ht * (2 - m_anchor.vertical()) / 2;
			//vbo data
			for (unsigned i = 0; i < m_text.length(); i++)
			{
				if (m_text[i] >= 32)
				{
					//character
					font->character(m_text[i]).coordinates(tc);
					const int w = font->character(m_text[i]).width();
					const int h = font->character(m_text[i]).height();
					const int r = font->character(m_text[i]).advance();
					const int a = font->character(m_text[i]).bearing(0);
					const int b = font->character(m_text[i]).bearing(1);
					//position
					xc[2 * 0 + 0] = xc[2 * 3 + 0] = xa[0] + xs[0] + ps * a;
					xc[2 * 2 + 1] = xc[2 * 3 + 1] = xa[1] + xs[1] + ps * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = xa[0] + xs[0] + ps * (a + w);
					xc[2 * 0 + 1] = xc[2 * 1 + 1] = xa[1] + xs[1] + ps * (b - h);
					//vertices
					for (unsigned j = 0; j < 4; j++)
					{
						(vbo_ptr + j)->m_color = m_color_fill;
						(vbo_ptr + j)->m_texture_coordinates = tc + 2 * j;
						(vbo_ptr + j)->m_position = m_position + xc[2 * j + 0] * t1 + xc[2 * j + 1] * t2;
					}
					vbo_ptr += 4;
					xs[0] += ps * r;
				}
				if (m_text[i] == '\t')
				{
					xs[0] += 4 * ps * font->character(' ').advance();
				}
				if (m_text[i] == '\n')
				{
					xs[0] = 0;
					xs[1] -= ps * (m_lines[2 * line + 1] + m_lines[2 * line + 2] + m_line_spacing * font->height());
				}
				if (m_text[i] == '\v')
				{
					xs[1] -= ps * (m_lines[2 * line + 1] + m_lines[2 * line + 2] + m_line_spacing * font->height());
				}
			}
		}

		void Text::setup(unsigned vbo_counter[], unsigned ibo_counter[])
		{
			//check
			unsigned a = 0, b = 0;
			if (m_font >= m_scene->fonts().size())
			{
				fprintf(stderr, "Error: Text's font has out of range index!\n");
				exit(EXIT_FAILURE);
			}
			//lines
			for (char c : m_text)
			{
				if (c == '\n' || c == '\v')
				{
					m_lines.push_back(a), m_lines.push_back(b), a = b = 0;
				}
				else
				{
					const Font *font = m_scene->font(m_font);
					a = std::max(a, font->character(c).bearing(1));
					b = std::max(b, font->character(c).height() - font->character(c).bearing(1));
				}
			}
			m_lines.push_back(a), m_lines.push_back(b);
			//indexes
			Object::setup(vbo_counter, ibo_counter);
		}
		void Text::buffers_data(vertices::Vertex **vbo_data, unsigned **ibo_data) const
		{
			if (m_fill)
				vbo_fill_data(vbo_data);
			if (m_fill)
				ibo_fill_data(ibo_data);
		}
	}
}