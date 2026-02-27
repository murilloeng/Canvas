//std
#include <cmath>

//Canvas
#include "Canvas/Canvas/inc/API/API.hpp"
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
				m_color{"white"}, m_grid_opacity{0.1f}, m_thickness{2}, m_graph{graph}, m_shaders{"Line2D", "Glyph2D"}
			{
				//vbos setup
				m_vbos[0].vertex_size(sizeof(vertices::Line2D));
				m_vbos[1].vertex_size(sizeof(vertices::Glyph2D));
				//vao setup: Line2D
				m_vaos[0].binding_divisor(0, 1);
				for(uint32_t i = 0; i < 4; i++) m_vaos[0].attribute_enable(i);
				for(uint32_t i = 0; i < 4; i++) m_vaos[0].attribute_binding(i, 0);
				m_vaos[0].attribute_format(0, 4, GL_FLOAT, 0 * sizeof(float));
				m_vaos[0].attribute_format(1, 2, GL_FLOAT, 4 * sizeof(float));
				m_vaos[0].attribute_format(2, 2, GL_FLOAT, 6 * sizeof(float));
				m_vaos[0].attribute_format(3, 1, GL_FLOAT, 8 * sizeof(float));
				m_vaos[0].vertex_buffer(0, m_vbos[0].id(), 0, sizeof(vertices::Line2D));
				//vao setup: Glyph2D
				for(uint32_t i = 0; i < 9; i++)
				{
					m_vaos[1].attribute_enable(i);
					m_vaos[1].attribute_binding(i, 0);
				}
				m_vaos[1].binding_divisor(0, 1);
				m_vaos[1].attribute_format(0, 4, GL_FLOAT,  0 * sizeof(float));
				for(uint32_t i = 0; i < 4; i++)
				{
					m_vaos[1].attribute_format(i + 1, 2, GL_FLOAT, ( 4 + 2 * i) * sizeof(float));
					m_vaos[1].attribute_format(i + 5, 2, GL_FLOAT, (12 + 2 * i) * sizeof(float));
				}
				m_vaos[1].vertex_buffer(0, m_vbos[1].id(), 0, sizeof(vertices::Glyph2D));
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

			float Frame::grid_opacity(void) const
			{
				return m_grid_opacity;
			}
			float Frame::grid_opacity(float grid_opacity)
			{
				return m_grid_opacity = grid_opacity;
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

			//position
			vec2 Frame::ndc(const vec2& xp) const
			{
				//data
				const float v00 = m_axis[0].range(0);
				const float v01 = m_axis[0].range(1);
				const float v10 = m_axis[1].range(0);
				const float v11 = m_axis[1].range(1);
				const float ws = m_scene->camera().width();
				const float hs = m_scene->camera().height();
				//screen
				const float ms = fminf(ws, hs);
				const float x00 = -ws / ms + m_offset[0];
				const float x01 = +ws / ms - m_offset[1];
				const float x10 = -hs / ms + m_offset[2];
				const float x11 = +hs / ms - m_offset[3];
				//return
				return {
					(x01 - x00) * (xp[0] - v00) / (v01 - v00) + x00,
					(x11 - x10) * (xp[1] - v10) / (v11 - v10) + x10
				};
			}
			vec2 Frame::pixel(const vec2& xp) const
			{
				//data
				const float v00 = m_axis[0].range(0);
				const float v01 = m_axis[0].range(1);
				const float v10 = m_axis[1].range(0);
				const float v11 = m_axis[1].range(1);
				const float ws = m_scene->camera().width();
				const float hs = m_scene->camera().height();
				//screen
				const float ms = fminf(ws, hs);
				const float x00 = -ws / ms + m_offset[0];
				const float x01 = +ws / ms - m_offset[1];
				const float x10 = -hs / ms + m_offset[2];
				const float x11 = +hs / ms - m_offset[3];
				//return
				return {
					(ms * ((x01 - x00) * (xp[0] - v00) / (v01 - v00) + x00) + ws) / 2,
					(ms * ((x11 - x10) * (xp[1] - v10) / (v11 - v10) + x10) + hs) / 2
				};
			}

			//draw
			void Frame::setup(void)
			{
				//data
				m_scene = m_graph->scene();
				const uint32_t n0 = m_axis[0].ticks_count();
				const uint32_t n1 = m_axis[1].ticks_count();
				//allocate
				m_vbos[1].allocate(9 * (n0 + n1));
				m_vbos[0].allocate(3 * (n0 + n1) - 8);
				vertices::Line2D* vbo_ptr_frame = (vertices::Line2D*) m_vbos[0].data();
				vertices::Glyph2D* vbo_ptr_ticks = (vertices::Glyph2D*) m_vbos[1].data();
				//buffers
				compute_offset();
				vbo_data_frame(vbo_ptr_frame);
				vbo_data_ticks_vertical(vbo_ptr_ticks);
				vbo_data_ticks_horizontal(vbo_ptr_ticks);
				//transfer
				m_vbos[0].transfer();
				m_vbos[1].transfer();
			}
			void Frame::draw(void) const
			{
				//draw frame
				m_vaos[0].bind();
				m_shaders[0].bind();
				glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, m_vbos[0].vertex_count());
				//draw ticks
				m_vaos[1].bind();
				m_shaders[1].bind();
				m_scene->font(m_graph->font())->texture().bind_unit(0);
				glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, m_vbos[1].vertex_count());
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
			void Frame::vbo_data_frame(vertices::Line2D*& vbo_ptr) const
			{
				//data
				for(uint32_t i = 0; i < m_vbos[0].vertex_count(); i++)
				{
					vbo_ptr[i].m_color = m_color;
					vbo_ptr[i].m_thickness = m_thickness;
				}
				//vbo data
				vbo_data_frame_grid(vbo_ptr);
				vbo_data_frame_vertical(vbo_ptr);
				vbo_data_frame_horizontal(vbo_ptr);
			}
			void Frame::vbo_data_frame_grid(vertices::Line2D*& vbo_ptr) const
			{
				//data
				const float ws = m_scene->camera().width();
				const float hs = m_scene->camera().height();
				const uint32_t n0 = m_axis[0].ticks_count();
				const uint32_t n1 = m_axis[1].ticks_count();
				const Color color(m_color[0], m_color[1], m_color[2], m_grid_opacity);
				//color
				for(uint32_t i = 0; i < n0 + n1 - 4; i++)
				{
					vbo_ptr[i].m_color = color;
				}
				//grid
				const float ms = fminf(ws, hs);
				float xi = -ws / ms + m_offset[0];
				float yi = -hs / ms + m_offset[2];
				for(uint32_t i = 1; i + 1 < n0; i++)
				{
					xi += (2 * ws / ms - m_offset[0] - m_offset[1]) / (n0 - 1);
					vbo_ptr->m_points[0] = {xi, -hs / ms + m_offset[2] + m_axis[0].ticks_size()};
					vbo_ptr->m_points[1] = {xi, +hs / ms - m_offset[3] - m_axis[0].ticks_size()};
					vbo_ptr++;
				}
				for(uint32_t i = 1; i + 1 < n1; i++)
				{
					yi += (2 * hs / ms - m_offset[2] - m_offset[3]) / (n1 - 1);
					vbo_ptr->m_points[0] = {-ws / ms + m_offset[0] + m_axis[1].ticks_size(), yi};
					vbo_ptr->m_points[1] = {+ws / ms - m_offset[1] - m_axis[1].ticks_size(), yi};
					vbo_ptr++;
				}
			}
			void Frame::vbo_data_frame_vertical(vertices::Line2D*& vbo_ptr) const
			{
				//data
				const float ws = m_scene->camera().width();
				const float hs = m_scene->camera().height();
				const uint32_t n1 = m_axis[1].ticks_count();
				//frame
				const float ms = fminf(ws, hs);
				float yi = -hs / ms + m_offset[2];
				vbo_ptr[0].m_points[0] = {-ws / ms + m_offset[0], -hs / ms + m_offset[2]};
				vbo_ptr[0].m_points[1] = {+ws / ms - m_offset[1], -hs / ms + m_offset[2]};
				vbo_ptr[1].m_points[0] = {-ws / ms + m_offset[0], +hs / ms - m_offset[3]};
				vbo_ptr[1].m_points[1] = {+ws / ms - m_offset[1], +hs / ms - m_offset[3]};
				//ticks
				vbo_ptr += 2;
				for(uint32_t i = 1; i + 1 < n1; i++)
				{
					yi += (2 * hs / ms - m_offset[2] - m_offset[3]) / (n1 - 1);
					vbo_ptr[0].m_points[0] = {-ws / ms + m_offset[0], yi};
					vbo_ptr[1].m_points[0] = {+ws / ms - m_offset[1], yi};
					vbo_ptr[0].m_points[1] = {-ws / ms + m_offset[0] + m_axis[1].ticks_size(), yi};
					vbo_ptr[1].m_points[1] = {+ws / ms - m_offset[1] - m_axis[1].ticks_size(), yi};
					vbo_ptr += 2;
				}
			}
			void Frame::vbo_data_frame_horizontal(vertices::Line2D*& vbo_ptr) const
			{
				//data
				const float ws = m_scene->camera().width();
				const float hs = m_scene->camera().height();
				const uint32_t n0 = m_axis[0].ticks_count();
				//frame
				const float ms = fminf(ws, hs);
				float xi = -ws / ms + m_offset[0];
				vbo_ptr[0].m_points[0] = {-ws / ms + m_offset[0], -hs / ms + m_offset[2]};
				vbo_ptr[0].m_points[1] = {-ws / ms + m_offset[0], +hs / ms - m_offset[3]};
				vbo_ptr[1].m_points[0] = {+ws / ms - m_offset[1], -hs / ms + m_offset[2]};
				vbo_ptr[1].m_points[1] = {+ws / ms - m_offset[1], +hs / ms - m_offset[3]};
				//ticks
				vbo_ptr += 2;
				for(uint32_t i = 1; i + 1 < n0; i++)
				{
					xi += (2 * ws / ms - m_offset[0] - m_offset[1]) / (n0 - 1);
					vbo_ptr[0].m_points[0] = {xi, -hs / ms + m_offset[2]};
					vbo_ptr[1].m_points[0] = {xi, +hs / ms - m_offset[3]};
					vbo_ptr[0].m_points[1] = {xi, -hs / ms + m_offset[2] + m_axis[0].ticks_size()};
					vbo_ptr[1].m_points[1] = {xi, +hs / ms - m_offset[3] - m_axis[0].ticks_size()};
					vbo_ptr += 2;
				}
			}

			void Frame::vbo_data_ticks_vertical(vertices::Glyph2D*& vbo_ptr) const
			{
				//data
				char string[256];
				float tc[8], xc[8];
				const float v10 = m_axis[1].range(0);
				const float v11 = m_axis[1].range(1);
				const float ws = m_scene->camera().width();
				const float hs = m_scene->camera().height();
				const uint32_t n1 = m_axis[1].ticks_count();
				const fonts::Font* font = m_scene->font(m_graph->font());
				//vbo data
				const float ms = fminf(ws, hs);
				for(uint32_t i = 0; i < n1; i++)
				{
					//string
					sprintf(string, "%+.2e", v10 + i * (v11 - v10) / (n1 - 1));
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
						vbo_ptr->m_color = m_color;
						for(uint32_t j = 0; j < 4; j++)
						{
							vbo_ptr->m_position[j] = xc + 2 * j;
							vbo_ptr->m_texture_coordinates[j] = tc + 2 * j;
						}
						vbo_ptr++;
						xi += m_axis[0].font_size() * r / font->height();
					}
				}
			}
			void Frame::vbo_data_ticks_horizontal(vertices::Glyph2D*& vbo_ptr) const
			{
				//data
				char string[256];
				float tc[8], xc[8];
				const float v00 = m_axis[0].range(0);
				const float v01 = m_axis[0].range(1);
				const float ws = m_scene->camera().width();
				const float hs = m_scene->camera().height();
				const uint32_t n0 = m_axis[0].ticks_count();
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
						vbo_ptr->m_color = m_color;
						for(uint32_t j = 0; j < 4; j++)
						{
							vbo_ptr->m_position[j] = xc + 2 * j;
							vbo_ptr->m_texture_coordinates[j] = tc + 2 * j;
						}
						vbo_ptr++;
						xi += m_axis[0].font_size() * r / font->height();
					}
				}
			}
		}
	}
}