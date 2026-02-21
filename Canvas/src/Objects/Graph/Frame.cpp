//std
#include <cmath>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Font.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Graph.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Frame.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			//constructors
			Frame::Frame(const Graph* graph) : 
				m_color{"white"}, m_thickness{3}, m_graph{graph}, m_shaders{
					{{new shaders::Stage(GL_VERTEX_SHADER, "Text2D.vert"), new shaders::Stage(GL_FRAGMENT_SHADER, "Text2D.frag")}},
					{{new shaders::Stage(GL_VERTEX_SHADER, "Model2D.vert"), new shaders::Stage(GL_FRAGMENT_SHADER, "Model2D.frag")}}
				}
			{
				//vbos setup
				m_vbos[0].vertex_size(sizeof(vertices::Text2D));
				m_vbos[1].vertex_size(sizeof(vertices::Model2D));
				//vao setup: Text2D
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
				m_vaos[0].vertex_buffer(0, m_vbos[0].id(), 0, sizeof(vertices::Text2D));
				//vao setup: Model2D
				m_vaos[1].attribute_enable(0);
				m_vaos[1].attribute_enable(1);
				m_vaos[1].attribute_binding(0, 0);
				m_vaos[1].attribute_binding(1, 0);
				m_vaos[1].element_buffer(m_ibos[1].id());
				m_vaos[1].attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
				m_vaos[1].attribute_format(1, 4, GL_FLOAT, 2 * sizeof(float));
				m_vaos[1].vertex_buffer(0, m_vbos[1].id(), 0, sizeof(vertices::Model2D));
			}
			
			//destructor
			Frame::~Frame(void)
			{
				return;
			}

			//data
			Axis& Frame::axis(uint32_t index)
			{
				return m_axis[index];
			}

			Color Frame::color(void) const
			{
				return m_color;
			}
			Color Frame::color(const Color& color)
			{
				return m_color = color;
			}

			uint32_t Frame::thickness(void) const
			{
				return m_thickness;
			}
			uint32_t Frame::thickness(uint32_t thickness)
			{
				return m_thickness = thickness;
			}

			//compute
			void Frame::compute_offset(void)
			{
				//data
				const float v00 = m_axis[0].range(0);
				const float v01 = m_axis[0].range(1);
				const float v10 = m_axis[1].range(0);
				const float v11 = m_axis[1].range(1);
				const float f0 = m_axis[0].font_size();
				const float f1 = m_axis[1].font_size();
				const uint32_t n0 = m_axis[0].ticks_count();
				const uint32_t n1 = m_axis[1].ticks_count();
				//horizontal
				m_offset[0] = text_width(f0, v00) / 2;
				m_offset[1] = text_width(f0, v01) / 2;
				for(uint32_t i = 0; i < n1; i++)
				{
					const float v1i = v10 + (v11 - v10) * i / (n1 - 1);
					m_offset[0] = fmaxf(m_offset[0], text_width(f1, v1i));
				}
				//vertical
				m_offset[2] = 0;
				for(uint32_t i = 0; i < n0; i++)
				{
					const float v0i = v00 + (v01 - v00) * i / (n0 - 1);
					m_offset[2] = fmaxf(m_offset[2], text_height(f0, v0i));
				}
				m_offset[3] = text_height(f1, v11) / 2;
				m_offset[2] += text_height(f1, v10) / 2;
			}

			//draw
			void Frame::setup(void)
			{
				//data
				m_scene = m_graph->scene();
				const uint32_t n0 = m_axis[0].ticks_count();
				const uint32_t n1 = m_axis[1].ticks_count();
				//allocate
				m_vbos[0].allocate(36 * (n0 + n1));
				m_ibos[0].allocate(54 * (n0 + n1));
				m_vbos[1].allocate(4 * (n0 + n1 - 3));
				m_ibos[1].allocate(4 * (n0 + n1 - 2));
				uint32_t* ibo_ptr_text = m_ibos[0].data();
				uint32_t* ibo_ptr_model = m_ibos[1].data();
				vertices::Text2D* vbo_ptr_text = (vertices::Text2D*) m_vbos[0].data();
				vertices::Model2D* vbo_ptr_model = (vertices::Model2D*) m_vbos[1].data();
				//buffers
				compute_offset();
				vbo_data_text(vbo_ptr_text);
				ibo_data_text(ibo_ptr_text);
				vbo_data_model(vbo_ptr_model);
				ibo_data_model(ibo_ptr_model);
				//transfer
				m_ibos[0].transfer();
				m_vbos[0].transfer();
				m_vbos[1].transfer();
				m_ibos[1].transfer();
			}
			void Frame::draw(void) const
			{
				//draw text
				m_vaos[0].bind();
				m_shaders[0].bind();
				m_scene->font(m_graph->font())->texture().bind_unit(0);
				glDrawElements(GL_TRIANGLES, m_ibos[0].vertex_count(), GL_UNSIGNED_INT, nullptr);
				//draw model
				m_vaos[1].bind();
				m_shaders[1].bind();
				glDrawElements(GL_LINES, m_ibos[1].vertex_count(), GL_UNSIGNED_INT, nullptr);
			}

			//text
			float Frame::text_width(float font_size, float value) const
			{
				char string[256];
				sprintf(string, "%+.2e", value);
				return text_width(font_size, string);
			}
			float Frame::text_width(float font_size, std::string text) const
			{
				//data
				float width = 0;
				const fonts::Font* font = m_scene->font(m_graph->font());
				//width
				for(char c : text)
				{
					width += font_size * font->glyph(c).advance() / font->height();
				}
				//return
				return width;
			}

			float Frame::text_height(float font_size, float value) const
			{
				char string[256];
				sprintf(string, "%+.2e", value);
				return text_height(font_size, string);
			}
			float Frame::text_height(float font_size, std::string text) const
			{
				//data
				float a = 0, b = 0;
				const fonts::Font* font = m_scene->font(m_graph->font());
				//width
				for(char c : text)
				{
					a = fmaxf(a, font_size * font->glyph(c).bearing(1) / font->height());
					b = fmaxf(b, font_size * (font->glyph(c).height() - font->glyph(c).bearing(1)) / font->height());
				}
				//return
				return a + b;
			}

			//bufers
			void Frame::ibo_data_text(uint32_t* ibo_ptr) const
			{
				//data
				const uint32_t n0 = m_axis[0].ticks_count();
				const uint32_t n1 = m_axis[1].ticks_count();
				//ibo data
				for(uint32_t i = 0; i < 9 * (n0 + n1); i++)
				{
					ibo_ptr[6 * i + 0] = 4 * i + 0;
					ibo_ptr[6 * i + 1] = 4 * i + 1;
					ibo_ptr[6 * i + 2] = 4 * i + 2;
					ibo_ptr[6 * i + 3] = 4 * i + 0;
					ibo_ptr[6 * i + 4] = 4 * i + 2;
					ibo_ptr[6 * i + 5] = 4 * i + 3;
				}
			}
			void Frame::vbo_data_text(vertices::Text2D* vbo_ptr) const
			{
				//data
				char string[256];
				float tc[8], xc[8];
				const float v00 = m_axis[0].range(0);
				const float v01 = m_axis[0].range(1);
				const float v10 = m_axis[1].range(0);
				const float v11 = m_axis[1].range(1);
				const float ws = m_scene->camera().width();
				const float hs = m_scene->camera().height();
				const uint32_t n0 = m_axis[0].ticks_count();
				const uint32_t n1 = m_axis[1].ticks_count();
				const fonts::Font* font = m_scene->font(m_graph->font());
				//vbo data
				const float ms = fminf(ws, hs);
				for(uint32_t i = 0; i < n0; i++)
				{
					//string
					sprintf(string, "%+.2e", v00 + i * (v01 - v00) / (n0 - 1));
					const float wi = text_width(m_axis[0].font_size(), string);
					//position
					const float yi = -hs / ms;
					float xi = -ws / ms + m_offset[0] + i * (2 * ws / ms - m_offset[0] - m_offset[1]) / (n0 - 1) - wi / 2;
					//glyphs
					for(char c : std::string(string))
					{
						//character
						font->glyph(c).coordinates(font, tc);
						const int32_t w = font->glyph(c).width();
						const int32_t h = font->glyph(c).height();
						const int32_t r = font->glyph(c).advance();
						const int32_t a = font->glyph(c).bearing(0);
						const int32_t b = font->glyph(c).bearing(1);
						//position
						xc[2 * 0 + 0] = xc[2 * 3 + 0] = xi + m_axis[0].font_size() * a / font->height();
						xc[2 * 2 + 1] = xc[2 * 3 + 1] = yi + m_axis[0].font_size() * b / font->height();
						xc[2 * 1 + 0] = xc[2 * 2 + 0] = xi + m_axis[0].font_size() * (a + w) / font->height();
						xc[2 * 0 + 1] = xc[2 * 1 + 1] = yi + m_axis[0].font_size() * (b - h) / font->height();
						//vertices
						for(uint32_t j = 0; j < 4; j++)
						{
							vbo_ptr[j].m_color = m_color;
							vbo_ptr[j].m_position = xc + 2 * j;
							vbo_ptr[j].m_texture_coordinates = tc + 2 * j;
						}
						vbo_ptr += 4;
						xi += m_axis[0].font_size() * r / font->height();
					}
				}
				for(uint32_t i = 0; i < n1; i++)
				{
					//string
					sprintf(string, "%+.2e", v10 + i * (v11 - v10) / (n0 - 1));
					const float hi = text_height(m_axis[1].font_size(), string);
					//position
					float xi = -ws / ms;
					const float yi = -hs / ms + m_offset[2] - (i != 0) * hi / 2 + (2 * hs / ms - m_offset[2] - m_offset[3]) * i / (n1 - 1);
					//glyphs
					for(char c : std::string(string))
					{
						//character
						font->glyph(c).coordinates(font, tc);
						const int32_t w = font->glyph(c).width();
						const int32_t h = font->glyph(c).height();
						const int32_t r = font->glyph(c).advance();
						const int32_t a = font->glyph(c).bearing(0);
						const int32_t b = font->glyph(c).bearing(1);
						//position
						xc[2 * 0 + 0] = xc[2 * 3 + 0] = xi + m_axis[0].font_size() * a / font->height();
						xc[2 * 2 + 1] = xc[2 * 3 + 1] = yi + m_axis[0].font_size() * b / font->height();
						xc[2 * 1 + 0] = xc[2 * 2 + 0] = xi + m_axis[0].font_size() * (a + w) / font->height();
						xc[2 * 0 + 1] = xc[2 * 1 + 1] = yi + m_axis[0].font_size() * (b - h) / font->height();
						//vertices
						for(uint32_t j = 0; j < 4; j++)
						{
							vbo_ptr[j].m_color = m_color;
							vbo_ptr[j].m_position = xc + 2 * j;
							vbo_ptr[j].m_texture_coordinates = tc + 2 * j;
						}
						vbo_ptr += 4;
						xi += m_axis[0].font_size() * r / font->height();
					}
				}
			}

			void Frame::ibo_data_model(uint32_t* ibo_ptr) const
			{
				//data
				const uint32_t n0 = m_axis[0].ticks_count();
				const uint32_t n1 = m_axis[1].ticks_count();
				//frame
				ibo_ptr[2 * 0 + 0] = ibo_ptr[2 * 3 + 1] = 0;
				ibo_ptr[2 * 0 + 1] = ibo_ptr[2 * 1 + 0] = 1;
				ibo_ptr[2 * 1 + 1] = ibo_ptr[2 * 2 + 0] = 2;
				ibo_ptr[2 * 2 + 1] = ibo_ptr[2 * 3 + 0] = 3;
				//ticks
				ibo_ptr += 4;
				for(uint32_t i = 1; i + 1 < n0; i++)
				{
					ibo_ptr += 4;
					ibo_ptr[0] = 4 * i + 0;
					ibo_ptr[1] = 4 * i + 1;
					ibo_ptr[2] = 4 * i + 2;
					ibo_ptr[3] = 4 * i + 3;
				}
				for(uint32_t i = 1; i + 1 < n1; i++)
				{
					ibo_ptr += 4;
					ibo_ptr[0] = 4 * (i + n0 - 2) + 0;
					ibo_ptr[1] = 4 * (i + n0 - 2) + 1;
					ibo_ptr[2] = 4 * (i + n0 - 2) + 2;
					ibo_ptr[3] = 4 * (i + n0 - 2) + 3;
				}
			}
			void Frame::vbo_data_model(vertices::Model2D* vbo_ptr) const
			{
				//data
				const float ws = m_scene->camera().width();
				const float hs = m_scene->camera().height();
				const uint32_t n0 = m_axis[0].ticks_count();
				const uint32_t n1 = m_axis[1].ticks_count();
				//color
				for(uint32_t i = 0; i < 4 * (n0 + n1 - 3); i++) vbo_ptr[i].m_color = m_color;
				//position
				const float ms = fminf(ws, hs);
				vbo_ptr[0].m_position = {-ws / ms + m_offset[0], -hs / ms + m_offset[2]};
				vbo_ptr[1].m_position = {+ws / ms - m_offset[1], -hs / ms + m_offset[2]};
				vbo_ptr[2].m_position = {+ws / ms - m_offset[1], +hs / ms - m_offset[3]};
				vbo_ptr[3].m_position = {-ws / ms + m_offset[0], +hs / ms - m_offset[3]};
				for(uint32_t i = 1; i + 1 < n0; i++)
				{
					vbo_ptr += 4;
					const float xi = -ws / ms + m_offset[0] + i * (2 * ws / ms - m_offset[0] - m_offset[1]) / (n0 - 1);
					vbo_ptr[0].m_position = {xi, -hs / ms + m_offset[2]};
					vbo_ptr[2].m_position = {xi, +hs / ms - m_offset[3]};
					vbo_ptr[1].m_position = {xi, -hs / ms + m_offset[2] + m_axis[0].ticks_size()};
					vbo_ptr[3].m_position = {xi, +hs / ms - m_offset[3] - m_axis[0].ticks_size()};
				}
				for(uint32_t i = 1; i + 1 < n1; i++)
				{
					vbo_ptr += 4;
					const float yi = -hs / ms + m_offset[2] + i * (2 * hs / ms - m_offset[2] - m_offset[3]) / (n1 - 1);
					vbo_ptr[0].m_position = {-ws / ms + m_offset[0], yi};
					vbo_ptr[2].m_position = {+ws / ms - m_offset[1], yi};
					vbo_ptr[1].m_position = {-ws / ms + m_offset[0] + m_axis[0].ticks_size(), yi};
					vbo_ptr[3].m_position = {+ws / ms - m_offset[1] - m_axis[0].ticks_size(), yi};
				}
			}
		}
	}
}