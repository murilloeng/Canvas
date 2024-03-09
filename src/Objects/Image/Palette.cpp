//std
#include <cmath>

//canvas
#include "Canvas/inc/Scene/Font.hpp"
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Scene/Image.hpp"
#include "Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/inc/Vertices/Model2D.hpp"
#include "Canvas/inc/Objects/Image/Palette.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Palette::Palette(void) : m_min(0.0f), m_max(1.0f), m_size(0.10f), m_font(0), m_marks(11)
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

		unsigned Palette::font(void) const
		{
			return m_font;
		}
		unsigned Palette::font(unsigned font)
		{
			return m_font = font;
		}

		unsigned Palette::marks(void) const
		{
			return m_marks;
		}
		unsigned Palette::marks(unsigned marks)
		{
			return m_marks = marks;
		}

		//text
		unsigned Palette::text_width(const char* string) const
		{
			//data
			const unsigned nc = strlen(string);
			//width
			unsigned w = 0;
			for(unsigned i = 0; i < nc; i++)
			{
				w += m_scene->font(m_font)->character(string[i]).advance();
			}
			return w;
		}
		unsigned Palette::text_height(const char* string) const
		{
			//data
			unsigned a = 0, b = 0;
			const unsigned nc = strlen(string);
			const Font* font = m_scene->font(m_font);
			//height
			for(unsigned i = 0; i < nc; i++)
			{
				a = std::max(a, font->character(string[i]).bearing(1));
				b = std::max(b, font->character(string[i]).height() - font->character(string[i]).bearing(1));
			}
			return a + b;
		}

		//buffers
		unsigned Palette::vbo_size(unsigned index) const
		{
			return 2 * (m_marks + m_palette.size()) * (index == 3) + 36 * m_marks * (index == 5);
		}
		unsigned Palette::ibo_size(unsigned index) const
		{
			return (m_marks + 2) * (index == 7) + 2 * (m_palette.size() - 1) * (index == 8) + 18 * m_marks * (index == 10);
		}

		//draw
		void Palette::ibo_fill_data(unsigned** ibo_data) const
		{
			//data
			const unsigned nc = m_palette.size();
			unsigned* ibo_ptr = ibo_data[8] + m_ibo_index[8];
			//ibo data
			for(unsigned i = 0; i + 1 < nc; i++)
			{
				ibo_ptr[6 * i + 0] = m_vbo_index[3] + 2 * m_marks + 0 * nc + i + 0;
				ibo_ptr[6 * i + 1] = m_vbo_index[3] + 2 * m_marks + 1 * nc + i + 0;
				ibo_ptr[6 * i + 2] = m_vbo_index[3] + 2 * m_marks + 1 * nc + i + 1;
				ibo_ptr[6 * i + 3] = m_vbo_index[3] + 2 * m_marks + 0 * nc + i + 0;
				ibo_ptr[6 * i + 4] = m_vbo_index[3] + 2 * m_marks + 1 * nc + i + 1;
				ibo_ptr[6 * i + 5] = m_vbo_index[3] + 2 * m_marks + 0 * nc + i + 1;
			}
		}
		void Palette::ibo_text_data(unsigned** ibo_data) const
		{
			for(unsigned i = 0; i < 9 * m_marks; i++)
			{
				ibo_data[10][m_ibo_index[10] + 6 * i + 0] = m_vbo_index[5] + 4 * i + 0;
				ibo_data[10][m_ibo_index[10] + 6 * i + 1] = m_vbo_index[5] + 4 * i + 1;
				ibo_data[10][m_ibo_index[10] + 6 * i + 2] = m_vbo_index[5] + 4 * i + 2;
				ibo_data[10][m_ibo_index[10] + 6 * i + 3] = m_vbo_index[5] + 4 * i + 0;
				ibo_data[10][m_ibo_index[10] + 6 * i + 4] = m_vbo_index[5] + 4 * i + 2;
				ibo_data[10][m_ibo_index[10] + 6 * i + 5] = m_vbo_index[5] + 4 * i + 3;
			}
		}
		void Palette::ibo_stroke_data(unsigned** ibo_data) const
		{
			for(unsigned i = 0; i < m_marks; i++)
			{
				ibo_data[7][m_ibo_index[7] + 2 * i + 0] = m_vbo_index[3] + 0 * m_marks + i;
				ibo_data[7][m_ibo_index[7] + 2 * i + 1] = m_vbo_index[3] + 1 * m_marks + i;
			}
			ibo_data[7][m_ibo_index[7] + 2 * m_marks + 0] = m_vbo_index[3] + 0 * m_marks + 0;
			ibo_data[7][m_ibo_index[7] + 2 * m_marks + 2] = m_vbo_index[3] + 1 * m_marks + 0;
			ibo_data[7][m_ibo_index[7] + 2 * m_marks + 1] = m_vbo_index[3] + 0 * m_marks + m_marks - 1;
			ibo_data[7][m_ibo_index[7] + 2 * m_marks + 3] = m_vbo_index[3] + 1 * m_marks + m_marks - 1;
		}
		void Palette::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			const unsigned nc = m_palette.size();
			vertices::Model2D* vbo_ptr = (vertices::Model2D*) vbo_data[3] + m_vbo_index[3] + 2 * m_marks;
			//vbo data
			for(unsigned i = 0; i < nc; i++)
			{
				vbo_ptr[i + 0 * nc].m_position[0] = +0.90f;
				vbo_ptr[i + 1 * nc].m_position[0] = +0.95f;
				vbo_ptr[i + 0 * nc].m_position[1] = 1.90f * i / (nc - 1) - 0.95f;
				vbo_ptr[i + 1 * nc].m_position[1] = 1.90f * i / (nc - 1) - 0.95f;
				vbo_ptr[i + 0 * nc].m_color = m_palette.color(float(i) / (nc - 1), 0, 1);
				vbo_ptr[i + 1 * nc].m_color = m_palette.color(float(i) / (nc - 1), 0, 1);
			}
		}
		void Palette::vbo_text_data(vertices::Vertex** vbo_data) const
		{
			//data
			char string[10];
			float xs[2], xc[8], tc[8];
			const Font* font = m_scene->font(m_font);
			const float ps = m_size / font->pixels_size();
			const unsigned ws = m_scene->camera().width();
			const unsigned hs = m_scene->camera().height();
			vertices::Text2D* vbo_ptr = (vertices::Text2D*) vbo_data[5] + m_vbo_index[5];
			//vbo data
			const float ms = fminf(ws, hs);
			for(unsigned i = 0; i < m_marks; i++)
			{
				//string
				sprintf(string, "%+.2e", (m_max - m_min) * i / (m_marks - 1) + m_min);
				const unsigned wt = text_width(string);
				const unsigned ht = text_height(string);
				//vertices
				xs[0] = xs[1] = 0;
				for(unsigned j = 0; j < 9; j++)
				{
					//character
					font->character(string[j]).coordinates(tc);
					const int w = font->character(string[j]).width();
					const int h = font->character(string[j]).height();
					const int r = font->character(string[j]).advance();
					const int a = font->character(string[j]).bearing(0);
					const int b = font->character(string[j]).bearing(1);
					//position
					xc[2 * 0 + 0] = xc[2 * 3 + 0] = xs[0] - ms / ws * ps * wt + ms / ws * ps * a;
					xc[2 * 2 + 1] = xc[2 * 3 + 1] = xs[1] - ms / hs * ps * ht / 2 + ms / hs * ps * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = xs[0] - ms / ws * ps * wt + ms / ws * ps * (a + w);
					xc[2 * 0 + 1] = xc[2 * 1 + 1] = xs[1] - ms / hs * ps * ht / 2 + ms / hs * ps * (b - h);
					//vertices
					for(unsigned k = 0; k < 4; k++)
					{
						(vbo_ptr + k)->m_texture_coordinates = tc + 2 * k;
						(vbo_ptr + k)->m_position[0] = xc[2 * k + 0] + 0.90f;
						(vbo_ptr + k)->m_position[1] = xc[2 * k + 1] + 1.90f * i / (m_marks - 1) - 0.95f;
					}
					vbo_ptr += 4;
					xs[0] += ms / ws * ps * r;
				}
			}
		}
		void Palette::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model2D* vbo_ptr = (vertices::Model2D*) vbo_data[3] + m_vbo_index[3];
			//vbo data
			vbo_ptr[0].m_position = {+0.90f, -0.95f};
			vbo_ptr[1].m_position = {+0.95f, -0.95f};
			vbo_ptr[2].m_position = {+0.95f, +0.95f};
			vbo_ptr[3].m_position = {+0.90f, +0.95f};
			for(unsigned i = 0; i < m_marks; i++)
			{
				vbo_ptr[i + 0 * m_marks].m_position[0] = +0.90f;
				vbo_ptr[i + 1 * m_marks].m_position[0] = +0.95f;
				vbo_ptr[i + 0 * m_marks].m_position[1] = 1.90f * i / (m_marks - 1) - 0.95f;
				vbo_ptr[i + 1 * m_marks].m_position[1] = 1.90f * i / (m_marks - 1) - 0.95f;
			}
		}
		void Palette::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			vbo_fill_data(vbo_data);
			ibo_fill_data(ibo_data);
			vbo_text_data(vbo_data);
			ibo_text_data(ibo_data);
			vbo_stroke_data(vbo_data);
			ibo_stroke_data(ibo_data);
		}
	}
}