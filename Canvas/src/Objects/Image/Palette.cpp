//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Fonts/Font.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model2D.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Palette.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Palette::Palette(void) : 
			m_min{0.0f}, m_max{1.0f}, m_size{0.07f}, m_width{0.08f}, m_height{1.90f}, m_offset{0.02f}, m_font{0}, m_marks{11},
			m_shaders{
				{{new shaders::Stage(GL_VERTEX_SHADER, "text2D.vert"), new shaders::Stage(GL_FRAGMENT_SHADER, "text2D.frag")}},
				{{new shaders::Stage(GL_VERTEX_SHADER, "model2D.vert"), new shaders::Stage(GL_FRAGMENT_SHADER, "model2D.frag")}}
			}
		{
			//vao setup text2D
			m_vaos[0].attribute_enable(0);
			m_vaos[0].attribute_enable(1);
			m_vaos[0].attribute_enable(2);
			m_vaos[0].attribute_binding(0, 0);
			m_vaos[0].attribute_binding(1, 0);
			m_vaos[0].attribute_binding(2, 0);
			m_vaos[0].element_buffer(m_ibos[0].id());
			m_vaos[0].attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
			m_vaos[0].attribute_format(1, 4, GL_FLOAT, 2 * sizeof(float));
			m_vaos[0].attribute_format(2, 2, GL_FLOAT, 6 * sizeof(float));
			m_vaos[0].vertex_buffer(0, m_vbos[0].id(), 0, 8 * sizeof(float));
			//vao setup model2D
			m_vaos[1].attribute_enable(0);
			m_vaos[1].attribute_enable(1);
			m_vaos[1].attribute_binding(0, 0);
			m_vaos[1].attribute_binding(1, 0);
			m_vaos[1].element_buffer(m_ibos[1].id());
			m_vaos[1].attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
			m_vaos[1].attribute_format(1, 4, GL_FLOAT, 2 * sizeof(float));
			m_vaos[1].vertex_buffer(0, m_vbos[1].id(), 0, 6 * sizeof(float));
			//vbos setup
			m_vbos[0].vertex_size(sizeof(vertices::Text2D));
			m_vbos[1].vertex_size(sizeof(vertices::Model2D));
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

		float Palette::width(float width)
		{
			return m_width = width;
		}
		float Palette::width(void) const
		{
			return m_width;
		}

		float Palette::height(float height)
		{
			return m_height = height;
		}
		float Palette::height(void) const
		{
			return m_height;
		}

		float Palette::offset(float offset)
		{
			return m_offset = offset;
		}
		float Palette::offset(void) const
		{
			return m_offset;
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
			int64_t a = 0, b = 0;
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
		void Palette::ibo_data_text(uint32_t* ibo_ptr) const
		{
			for(uint32_t i = 0; i < 9 * m_marks; i++)
			{
				ibo_ptr[6 * i + 0] = 4 * i + 0;
				ibo_ptr[6 * i + 1] = 4 * i + 1;
				ibo_ptr[6 * i + 2] = 4 * i + 2;
				ibo_ptr[6 * i + 3] = 4 * i + 0;
				ibo_ptr[6 * i + 4] = 4 * i + 2;
				ibo_ptr[6 * i + 5] = 4 * i + 3;
			}
		}
		void Palette::ibo_data_model(uint32_t* ibo_ptr) const
		{
			//data
			const uint32_t nm = m_marks;
			const uint32_t nc = m_palette.size();
			//ibo data triangles
			for(uint32_t i = 0; i + 1 < nc; i++)
			{
				ibo_ptr[0] = 0 * nc + i + 0;
				ibo_ptr[1] = 1 * nc + i + 0;
				ibo_ptr[2] = 1 * nc + i + 1;
				ibo_ptr[3] = 0 * nc + i + 0;
				ibo_ptr[4] = 1 * nc + i + 1;
				ibo_ptr[5] = 0 * nc + i + 1;
				ibo_ptr += 6;
			}
			//ibo lines data
			for(uint32_t i = 0; i < nm; i++)
			{
				ibo_ptr[0] = 0 * nm + i;
				ibo_ptr[1] = 1 * nm + i;
				ibo_ptr += 2;
			}
			ibo_ptr[0] = 0 * nm + 0;
			ibo_ptr[2] = 1 * nm + 0;
			ibo_ptr[1] = 0 * nm + nm - 1;
			ibo_ptr[3] = 1 * nm + nm - 1;
		}
		void Palette::vbo_data_model(vertices::Model2D* vbo_ptr) const
		{
			//data
			const uint32_t nm = m_marks;
			const uint32_t nc = m_palette.size();
			const float ws = (float) m_scene->camera().width();
			const float hs = (float) m_scene->camera().height();
			const Color color = m_scene->background().inverse();
			//vbo data
			const float ms = fminf(ws, hs);
			for(uint32_t i = 0; i < nc; i++)
			{
				//colors
				vbo_ptr[i + 0 * nc].m_color = m_palette.color(float(i) / (nc - 1), 0, 1);
				vbo_ptr[i + 1 * nc].m_color = m_palette.color(float(i) / (nc - 1), 0, 1);
				//positions
				vbo_ptr[i + 1 * nc].m_position[0] = ws / ms - m_offset;
				vbo_ptr[i + 0 * nc].m_position[0] = ws / ms - m_offset - m_width;
				vbo_ptr[i + 1 * nc].m_position[1] = m_height * (float(i) / (nc - 1) - 0.5f);
				vbo_ptr[i + 0 * nc].m_position[1] = m_height * (float(i) / (nc - 1) - 0.5f);
			}
			for(uint32_t i = 0; i < nm; i++)
			{
				//colors
				vbo_ptr[2 * nc + i + 0 * nm].m_color = color;
				vbo_ptr[2 * nc + i + 1 * nm].m_color = color;
				//positions
				vbo_ptr[2 * nc + i + 1 * nm].m_position[0] = ws / ms - m_offset;
				vbo_ptr[2 * nc + i + 0 * nm].m_position[0] = ws / ms - m_offset - m_width;
				vbo_ptr[2 * nc + i + 1 * nm].m_position[1] = m_height * (float(i) / (nm - 1) - 0.5f);
				vbo_ptr[2 * nc + i + 0 * nm].m_position[1] = m_height * (float(i) / (nm - 1) - 0.5f);
			}
		}
		void Palette::vbo_data_text(vertices::Text2D* vbo_ptr) const
		{
			//data
			char string[10];
			float xp[2], xc[8], tc[8];
			const uint32_t nm = m_marks;
			const fonts::Font* font = m_scene->font(m_font);
			const float ws = (float) m_scene->camera().width();
			const float hs = (float) m_scene->camera().height();
			const Color color = m_scene->background().inverse();
			//vbo data
			const float ms = fminf(ws, hs);
			const float ps = m_size / font->height();
			for(uint32_t i = 0; i < m_marks; i++)
			{
				//string
				sprintf(string, "%+.2e", m_min + (m_max - m_min) * i / (nm - 1));
				//vertices
				const uint32_t wt = text_width(string);
				const uint32_t ht = text_height(string);
				xp[0] = ws / ms - m_width - m_offset - ps * wt;
				xp[1] = m_height * (float(i) / (nm - 1) - 0.5f) - ps * ht / 2;
				for(uint32_t j = 0; j < 9; j++)
				{
					//character
					font->glyph(string[j]).coordinates(font, tc);
					const int64_t w = font->glyph(string[j]).width();
					const int64_t h = font->glyph(string[j]).height();
					const int64_t r = font->glyph(string[j]).advance();
					const int64_t a = font->glyph(string[j]).bearing(0);
					const int64_t b = font->glyph(string[j]).bearing(1);
					//position
					xc[2 * 0 + 0] = xc[2 * 3 + 0] = xp[0] + ps * a;
					xc[2 * 2 + 1] = xc[2 * 3 + 1] = xp[1] + ps * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = xp[0] + ps * (a + w);
					xc[2 * 0 + 1] = xc[2 * 1 + 1] = xp[1] + ps * (b - h);
					//vertices
					for(uint32_t k = 0; k < 4; k++)
					{
						(vbo_ptr + k)->m_color = color;
						(vbo_ptr + k)->m_position = xc + 2 * k;
						(vbo_ptr + k)->m_texture_coordinates = tc + 2 * k;
					}
					vbo_ptr += 4;
					xp[0] += ps * r;
				}
			}
		}

		//draw
		void Palette::setup(void)
		{
			//data
			const uint32_t nm = m_marks;
			const uint32_t nc = m_palette.size();
			//allocate
			m_vbos[0].allocate(36 * nm);
			m_ibos[0].allocate(54 * nm);
			m_vbos[1].allocate(2 * (nc + nm));
			m_ibos[1].allocate(6 * (nc - 1) + 2 * (nm + 2));
			//pointers
			uint32_t* ibo_ptr_text = m_ibos[0].data();
			uint32_t* ibo_ptr_model = m_ibos[1].data();
			vertices::Text2D* vbo_ptr_text = (vertices::Text2D*) m_vbos[0].data();
			vertices::Model2D* vbo_ptr_model = (vertices::Model2D*) m_vbos[1].data();
			//buffers data
			vbo_data_text(vbo_ptr_text);
			ibo_data_text(ibo_ptr_text);
			vbo_data_model(vbo_ptr_model);
			ibo_data_model(ibo_ptr_model);
			//transfer
			m_ibos[0].transfer();
			m_vbos[0].transfer();
			m_ibos[1].transfer();
			m_vbos[1].transfer();
		}
		void Palette::draw(void) const
		{
			//data
			const uint32_t nm = m_marks;
			const uint32_t nc = m_palette.size();
			//draw text
			m_vaos[0].bind();
			m_shaders[0].bind();
			m_scene->font(m_font)->texture().bind_unit(0);
			glDrawElements(GL_TRIANGLES, 54 * nm, GL_UNSIGNED_INT, nullptr);
			//draw model
			m_vaos[1].bind();
			m_shaders[1].bind();
			glDrawElements(GL_TRIANGLES, 6 * (nc - 1), GL_UNSIGNED_INT, nullptr);
			glDrawElementsBaseVertex(GL_LINES, 2 * (nm + 2), GL_UNSIGNED_INT, (void*) (6 * (nc - 1) * sizeof(uint32_t)), 2 * nc);
		}
	}
}