//std
#include <cmath>
#include <stdexcept>

//canvas
#include "Canvas/inc/Fonts/Font.hpp"
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/inc/Objects/Image/Text2D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Text2D::Text2D(void) : m_font{0}, m_shader{"Text2D"}
		{
			//vao setup
			m_vao.attribute_enable(0);
			m_vao.attribute_enable(1);
			m_vao.attribute_enable(2);
			m_vao.attribute_binding(0, 0);
			m_vao.attribute_binding(1, 0);
			m_vao.attribute_binding(2, 0);
			m_vao.element_buffer(m_ibo.id());
			m_vao.vertex_buffer(0, m_vbo.id(), 0, 8 * sizeof(float));
			m_vao.attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
			m_vao.attribute_format(1, 4, GL_FLOAT, 2 * sizeof(float));
			m_vao.attribute_format(2, 2, GL_FLOAT, 6 * sizeof(float));
			//vbo setup
			m_vbo.vertex_size(sizeof(vertices::Text2D));
		}

		//destructor
		Text2D::~Text2D(void)
		{
			return;
		}

		//data
		uint32_t Text2D::font(void) const
		{
			return m_font;
		}
		uint32_t Text2D::font(uint32_t font)
		{
			return m_font = font;
		}

		Color Text2D::color(void) const
		{
			return m_color;
		}
		Color Text2D::color(const Color& color)
		{
			return m_color = color;
		}

		Anchor Text2D::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Text2D::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		std::string Text2D::text(void) const
		{
			return m_text;
		}
		std::string Text2D::text(std::string text)
		{
			return m_text = text;
		}

		//text
		uint32_t Text2D::width(void) const
		{
			//data
			uint32_t v = 0, w = 0;
			const fonts::Font* font = m_scene->font(m_font);
			//width
			for(char c : m_text)
			{
				if(c == '\n')
				{
					w = std::max(w, v), v = 0;
				}
				else
				{
					v += font->glyph(c).advance();
				}
			}
			return std::max(w, v);
		}
		uint32_t Text2D::height(void) const
		{
			//data
			fonts::Font* font = m_scene->font(m_font);
			uint32_t h = font->ascender() - font->descender();
			//height
			for(char c : m_text)
			{
				if(c == '\n' || c == '\v')
				{
					h += font->height();
				}
			}
			return h;
		}
		uint32_t Text2D::length(void) const
		{
			uint32_t v = 0;
			for(char c : m_text)
			{
				if(c >= 32) v++;
			}
			return v;
		}

		//data
		void Text2D::ibo_data(uint32_t nc, uint32_t* ibo_ptr) const
		{
			for(uint32_t i = 0; i < nc; i++)
			{
				ibo_ptr[6 * i + 0] = 4 * i + 0;
				ibo_ptr[6 * i + 1] = 4 * i + 1;
				ibo_ptr[6 * i + 2] = 4 * i + 2;
				ibo_ptr[6 * i + 3] = 4 * i + 0;
				ibo_ptr[6 * i + 4] = 4 * i + 2;
				ibo_ptr[6 * i + 5] = 4 * i + 3;
			}
		}
		void Text2D::vbo_data(uint32_t nc, vertices::Text2D* vbo_ptr) const
		{
			//data
			float xc[8], tc[8];
			const uint32_t wt = width();
			const uint32_t ht = height();
			const fonts::Font *font = m_scene->font(m_font);
			const uint32_t a2 = uint32_t(m_anchor.vertical());
			const uint32_t a1 = uint32_t(m_anchor.horizontal());
			//pen position
			const float ps = 1.0f / font->height();
			float xp[] = {0, -ps * font->ascender()};
			const float xa[] = {-ps * wt * a1 / 2, ps * ht * (2 - a2) / 2};
			//vbo data
			for(char c : m_text)
			{
				if(c >= 32)
				{
					//character
					font->glyph(c).coordinates(font, tc);
					const int32_t w = font->glyph(c).width();
					const int32_t h = font->glyph(c).height();
					const int32_t r = font->glyph(c).advance();
					const int32_t a = font->glyph(c).bearing(0);
					const int32_t b = font->glyph(c).bearing(1);
					//position
					xc[2 * 0 + 0] = xc[2 * 3 + 0] = xp[0] + xa[0] + ps * a;
					xc[2 * 2 + 1] = xc[2 * 3 + 1] = xp[1] + xa[1] + ps * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = xp[0] + xa[0] + ps * (a + w);
					xc[2 * 0 + 1] = xc[2 * 1 + 1] = xp[1] + xa[1] + ps * (b - h);
					//vertices
					for(uint32_t j = 0; j < 4; j++)
					{
						vbo_ptr[j].m_color = m_color;
						vbo_ptr[j].m_texture_coordinates = tc + 2 * j;
						vbo_ptr[j].m_position = m_model_matrix * vec2(xc + 2 * j);
					}
					vbo_ptr += 4;
					xp[0] += ps * r;
				}
				if(c == '\v') xp[1] -= 1;
				if(c == '\n') xp[1] -= 1, xp[0] = 0;
				if(c == '\t') xp[0] += ps * font->glyph('\t').advance();
			}
		}

		//draw
		void Text2D::setup(void)
		{
			//data
			const uint32_t nc = length();
			//allocate
			m_vbo.allocate(4 * nc);
			m_ibo.allocate(6 * nc);
			uint32_t* ibo_ptr = m_ibo.data();
			vertices::Text2D* vbo_ptr = (vertices::Text2D*) m_vbo.data();
			//buffers data
			ibo_data(nc, ibo_ptr);
			vbo_data(nc, vbo_ptr);
			//transfer
			m_vbo.transfer();
			m_ibo.transfer();
		}
		void Text2D::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			const uint32_t ni = m_ibo.vertex_count();
			m_scene->font(m_font)->texture().bind_unit(0);
			glDrawElements(GL_TRIANGLES, ni, GL_UNSIGNED_INT, nullptr);
		}
	}
}