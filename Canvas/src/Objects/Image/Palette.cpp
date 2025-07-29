//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Fonts/Font.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Textures/Image.hpp"

#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model2D.hpp"

#include "Canvas/Canvas/inc/Objects/Image/Palette.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Palette::Palette(void) : m_min(0.0f), m_max(1.0f), m_size(0.08f), m_font(0), m_marks(11)
		{
			return;
		}

		//destructor
		Palette::~Palette(void)
		{
			return;
		}

		//data
		float Palette::min(float min)
		{
			return m_min = min;
		}
		float Palette::min(void) const
		{
			return m_min;
		}

		float Palette::max(float max)
		{
			return m_max = max;
		}
		float Palette::max(void) const
		{
			return m_max;
		}

		float Palette::size(float size)
		{
			return m_size = size;
		}
		float Palette::size(void) const
		{
			return m_size;
		}

		uint32_t Palette::font(void) const
		{
			return m_font;
		}
		uint32_t Palette::font(uint32_t font)
		{
			return m_font = font;
		}

		uint32_t Palette::marks(void) const
		{
			return m_marks;
		}
		uint32_t Palette::marks(uint32_t marks)
		{
			return m_marks = marks;
		}

		palettes::Palette& Palette::palette(void)
		{
			return m_palette;
		}

		//text
		uint32_t Palette::text_width(const char* string) const
		{
			//data
			const uint32_t nc = (uint32_t) strlen(string);
			//width
			uint32_t w = 0;
			for(uint32_t i = 0; i < nc; i++)
			{
				w += m_scene->font(m_font)->glyph(string[i]).advance();
			}
			return w;
		}
		uint32_t Palette::text_height(const char* string) const
		{
			//data
			uint32_t a = 0, b = 0;
			const fonts::Font* font = m_scene->font(m_font);
			const uint32_t nc = (uint32_t) strlen(string);
			//height
			for(uint32_t i = 0; i < nc; i++)
			{
				a = std::max(a, font->glyph(string[i]).bearing(1));
				b = std::max(b, font->glyph(string[i]).height() - font->glyph(string[i]).bearing(1));
			}
			return a + b;
		}

		//data
		void Palette::ibo_fill_data(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(8);
			const uint32_t nc = m_palette.size();
			//ibo data
			for(uint32_t i = 0; i + 1 < nc; i++)
			{
				ibo_ptr[6 * i + 0] = m_vbo_index[3] + 2 * m_marks + 0 * nc + i + 0;
				ibo_ptr[6 * i + 1] = m_vbo_index[3] + 2 * m_marks + 1 * nc + i + 0;
				ibo_ptr[6 * i + 2] = m_vbo_index[3] + 2 * m_marks + 1 * nc + i + 1;
				ibo_ptr[6 * i + 3] = m_vbo_index[3] + 2 * m_marks + 0 * nc + i + 0;
				ibo_ptr[6 * i + 4] = m_vbo_index[3] + 2 * m_marks + 1 * nc + i + 1;
				ibo_ptr[6 * i + 5] = m_vbo_index[3] + 2 * m_marks + 0 * nc + i + 1;
			}
		}
		void Palette::ibo_text_data(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(10);
			//ibo data
			for(uint32_t i = 0; i < 9 * m_marks; i++)
			{
				ibo_ptr[6 * i + 0] = m_vbo_index[5] + 4 * i + 0;
				ibo_ptr[6 * i + 1] = m_vbo_index[5] + 4 * i + 1;
				ibo_ptr[6 * i + 2] = m_vbo_index[5] + 4 * i + 2;
				ibo_ptr[6 * i + 3] = m_vbo_index[5] + 4 * i + 0;
				ibo_ptr[6 * i + 4] = m_vbo_index[5] + 4 * i + 2;
				ibo_ptr[6 * i + 5] = m_vbo_index[5] + 4 * i + 3;
			}
		}
		void Palette::ibo_stroke_data(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(7);
			//ibo data
			for(uint32_t i = 0; i < m_marks; i++)
			{
				ibo_ptr[2 * i + 0] = m_vbo_index[3] + 0 * m_marks + i;
				ibo_ptr[2 * i + 1] = m_vbo_index[3] + 1 * m_marks + i;
			}
			ibo_ptr[2 * m_marks + 0] = m_vbo_index[3] + 0 * m_marks + 0;
			ibo_ptr[2 * m_marks + 2] = m_vbo_index[3] + 1 * m_marks + 0;
			ibo_ptr[2 * m_marks + 1] = m_vbo_index[3] + 0 * m_marks + m_marks - 1;
			ibo_ptr[2 * m_marks + 3] = m_vbo_index[3] + 1 * m_marks + m_marks - 1;
		}
		void Palette::vbo_fill_data(void) const
		{
			//data
			const uint32_t nc = m_palette.size();
			vertices::Model2D* vbo_ptr = vbo_data_model_2D() + 2 * m_marks;
			//vbo data
			for(uint32_t i = 0; i < nc; i++)
			{
				vbo_ptr[i + 0 * nc].m_position[0] = +0.90f;
				vbo_ptr[i + 1 * nc].m_position[0] = +0.95f;
				vbo_ptr[i + 0 * nc].m_position[1] = 1.90f * i / (nc - 1) - 0.95f;
				vbo_ptr[i + 1 * nc].m_position[1] = 1.90f * i / (nc - 1) - 0.95f;
				vbo_ptr[i + 0 * nc].m_color = m_palette.color(float(i) / (nc - 1), 0, 1);
				vbo_ptr[i + 1 * nc].m_color = m_palette.color(float(i) / (nc - 1), 0, 1);
			}
		}
		void Palette::vbo_text_data(void) const
		{
			//data
			char string[10];
			float xs[2], xc[8], tc[8];
			const fonts::Font* font = m_scene->font(m_font);
			const float ps = m_size / font->pixels_size();
			vertices::Text2D* vbo_ptr = vbo_data_text_2D();
			const float ws = (float) m_scene->camera().width();
			const float hs = (float) m_scene->camera().height();
			const Color color = m_scene->background().inverse();
			//vbo data
			const float ms = fminf(ws, hs);
			for(uint32_t i = 0; i < m_marks; i++)
			{
				//string
				sprintf(string, "%+.2e", (m_max - m_min) * i / (m_marks - 1) + m_min);
				const uint32_t wt = text_width(string);
				const uint32_t ht = text_height(string);
				//vertices
				xs[0] = xs[1] = 0;
				for(uint32_t j = 0; j < 9; j++)
				{
					//character
					font->glyph(string[j]).coordinates(tc);
					const int w = font->glyph(string[j]).width();
					const int h = font->glyph(string[j]).height();
					const int r = font->glyph(string[j]).advance();
					const int a = font->glyph(string[j]).bearing(0);
					const int b = font->glyph(string[j]).bearing(1);
					//position
					xc[2 * 0 + 0] = xc[2 * 3 + 0] = xs[0] - ms / ws * ps * wt + ms / ws * ps * a;
					xc[2 * 2 + 1] = xc[2 * 3 + 1] = xs[1] - ms / hs * ps * ht / 2 + ms / hs * ps * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = xs[0] - ms / ws * ps * wt + ms / ws * ps * (a + w);
					xc[2 * 0 + 1] = xc[2 * 1 + 1] = xs[1] - ms / hs * ps * ht / 2 + ms / hs * ps * (b - h);
					//vertices
					for(uint32_t k = 0; k < 4; k++)
					{
						(vbo_ptr + k)->m_color = color;
						(vbo_ptr + k)->m_texture_coordinates = tc + 2 * k;
						(vbo_ptr + k)->m_position[0] = xc[2 * k + 0] + 0.90f;
						(vbo_ptr + k)->m_position[1] = xc[2 * k + 1] + 1.90f * i / (m_marks - 1) - 0.95f;
					}
					vbo_ptr += 4;
					xs[0] += ms / ws * ps * r;
				}
			}
		}
		void Palette::vbo_stroke_data(void) const
		{
			//data
			vertices::Model2D* vbo_ptr = vbo_data_model_2D();
			const Color color = m_scene->background().inverse();
			//vbo data
			vbo_ptr[0].m_position = {+0.90f, -0.95f};
			vbo_ptr[1].m_position = {+0.95f, -0.95f};
			vbo_ptr[2].m_position = {+0.95f, +0.95f};
			vbo_ptr[3].m_position = {+0.90f, +0.95f};
			for(uint32_t i = 0; i < m_marks; i++)
			{
				vbo_ptr[i + 0 * m_marks].m_color = color;
				vbo_ptr[i + 1 * m_marks].m_color = color;
				vbo_ptr[i + 0 * m_marks].m_position[0] = +0.90f;
				vbo_ptr[i + 1 * m_marks].m_position[0] = +0.95f;
				vbo_ptr[i + 0 * m_marks].m_position[1] = 1.90f * i / (m_marks - 1) - 0.95f;
				vbo_ptr[i + 1 * m_marks].m_position[1] = 1.90f * i / (m_marks - 1) - 0.95f;
			}
		}

		//buffers
		void Palette::buffers_size(void)
		{
			m_vbo_size[ 5] = 36 * m_marks;
			m_ibo_size[10] = 54 * m_marks;
			m_ibo_size[ 7] = 2 * (m_marks + 2);
			m_ibo_size[ 8] = 6 * (m_palette.size() - 1);
			m_vbo_size[ 3] = 2 * (m_marks + m_palette.size());
		}
		void Palette::buffers_data(void) const
		{
			vbo_fill_data();
			ibo_fill_data();
			vbo_text_data();
			ibo_text_data();
			vbo_stroke_data();
			ibo_stroke_data();
		}
	}
}