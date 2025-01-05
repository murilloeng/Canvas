//canvas
#include "Canvas/Canvas/inc/Scene/Font.hpp"
#include "Canvas/Canvas/inc/Scene/Latex.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Graph_2D.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			//constructors
			Graph_2D::Graph_2D(void) : 
				m_width(4), m_height(3), m_range{0, 1, 0, 1}, 
				m_labels_latex{false, false}, m_labels_size{0.12f, 0.12f}, m_labels_font{0, 0}, 
				m_labels_index{0, 0}, m_labels_string{"x1", "x2"},
				m_tics_font{0, 0}, m_tics_count{9, 9}, m_tics_format{"%.2f", "%.2f"}, 
				m_tics_line_size{0.06f, 0.06f}, m_tics_label_size{0.12f, 0.12f}
			{
				return;
			}

			//destructor
			Graph_2D::~Graph_2D(void)
			{
				for(const Curve_2D* curve : m_curves)
				{
					delete curve;
				}
			}

			//data
			float Graph_2D::width(void) const
			{
				return m_width;
			}
			float Graph_2D::width(float width)
			{
				return m_width = width;
			}

			float Graph_2D::height(void) const
			{
				return m_height;
			}
			float Graph_2D::height(float height)
			{
				return m_height = height;
			}

			float Graph_2D::range(uint32_t axis, uint32_t index) const
			{
				return m_range[2 * axis + index];
			}
			float Graph_2D::range(uint32_t axis, uint32_t index, float range)
			{
				return m_range[2 * axis + index] = range;
			}

			bool Graph_2D::labels_latex(uint32_t index) const
			{
				return m_labels_latex[index];
			}
			bool Graph_2D::labels_latex(uint32_t index, bool latex)
			{
				return m_labels_latex[index] = latex;
			}

			float Graph_2D::labels_size(float size)
			{
				return m_labels_size[0] = m_labels_size[1] = size;
			}
			float Graph_2D::labels_size(uint32_t index) const
			{
				return m_labels_size[index];
			}
			float Graph_2D::labels_size(uint32_t index, float size)
			{
				return m_labels_size[index] = size;
			}

			uint32_t Graph_2D::labels_index(uint32_t index) const
			{
				return m_labels_index[index];
			}
			uint32_t Graph_2D::labels_index(uint32_t index, uint32_t latex_index)
			{
				return m_labels_index[index] = latex_index;
			}

			const char* Graph_2D::labels_string(uint32_t index) const
			{
				return m_labels_string[index];
			}
			const char* Graph_2D::labels_string(uint32_t index, const char* string)
			{
				return strcpy(m_labels_string[index], string);
			}

			float Graph_2D::tics_line_size(float size)
			{
				return m_tics_line_size[0] = m_tics_line_size[1] = size;
			}
			float Graph_2D::tics_line_size(uint32_t index) const
			{
				return m_tics_line_size[index];
			}
			float Graph_2D::tics_line_size(uint32_t index, float size)
			{
				return m_tics_line_size[index] = size;
			}

			float Graph_2D::tics_label_size(float size)
			{
				return m_tics_label_size[0] = m_tics_label_size[1] = size;
			}
			float Graph_2D::tics_label_size(uint32_t index) const
			{
				return m_tics_label_size[index];
			}
			float Graph_2D::tics_label_size(uint32_t index, float size)
			{
				return m_tics_label_size[index] = size;
			}

			uint32_t Graph_2D::tics_font(uint32_t index) const
			{
				return m_tics_font[index];
			}
			uint32_t Graph_2D::tics_font(uint32_t index, uint32_t font)
			{
				return m_tics_font[index] = font;
			}

			uint32_t Graph_2D::tics_count(uint32_t index) const
			{
				return m_tics_count[index];
			}
			uint32_t Graph_2D::tics_count(uint32_t index, uint32_t tics)
			{
				return m_tics_count[index] = tics;
			}

			const char* Graph_2D::tics_format(const char* format)
			{
				return strcpy(m_tics_format[1], strcpy(m_tics_format[0], format));
			}
			const char* Graph_2D::tics_format(uint32_t index) const
			{
				return m_tics_format[index];
			}
			const char* Graph_2D::tics_format(uint32_t index, const char* format)
			{
				return strcpy(m_tics_format[index], format);
			}

			//curves
			std::vector<Curve_2D*>& Graph_2D::curves(void)
			{
				return m_curves;
			}
			const std::vector<Curve_2D*>& Graph_2D::curves(void) const
			{
				return m_curves;
			}

			//setup
			void Graph_2D::setup(void)
			{
				//data
				char label[20];
				const float a1 = m_range[2 * 0 + 0];
				const float a2 = m_range[2 * 0 + 1];
				const float b1 = m_range[2 * 1 + 0];
				const float b2 = m_range[2 * 1 + 1];
				const uint32_t n1 = m_tics_count[0];
				const uint32_t n2 = m_tics_count[1];
				//count
				m_tics_width = 0;
				m_tics_chars[0] = 0;
				m_tics_chars[1] = 0;
				for(uint32_t i = 0; i < n1 + 2; i++)
				{
					m_tics_chars[0] += sprintf(label, m_tics_format[0], a1 + i * (a2 - a1) / (n1 + 1));
				}
				for(uint32_t i = 0; i < n2 + 2; i++)
				{
					uint32_t width = 0;
					m_tics_chars[1] += sprintf(label, m_tics_format[1], b1 + i * (b2 - b1) / (n2 + 1));
					for(uint32_t j = 0; j < (uint32_t) strlen(label); j++)
					{
						width += m_scene->font(m_tics_font[1])->character(label[j]).advance();
					}
					m_tics_width = std::max(m_tics_width, width);
				}
				//setup
				Object::setup();
			}

			//buffers
			void Graph_2D::buffers_size(void)
			{
				//data
				const uint32_t n1 = m_tics_count[0];
				const uint32_t n2 = m_tics_count[1];
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t m2 = m_tics_chars[1];
				const uint32_t p1 = (uint32_t) strlen(m_labels_string[0]);
				const uint32_t p2 = (uint32_t) strlen(m_labels_string[1]);
				//sizes
				m_ibo_size[0] = 0;
				m_vbo_size[2] = 4 * (m1 + m2);
				m_ibo_size[4] = 6 * (m1 + m2);
				m_vbo_size[0] = 4 * (1 + n1 + n2);
				m_ibo_size[1] = 4 * (2 + n1 + n2);
				m_vbo_size[2] += 4 * (m_labels_latex[0] ? 1 : p1);
				m_vbo_size[2] += 4 * (m_labels_latex[1] ? 1 : p2);
				m_ibo_size[4] += 6 * (m_labels_latex[0] ? 0 : p1);
				m_ibo_size[4] += 6 * (m_labels_latex[1] ? 0 : p2);
				m_ibo_size[5] = 6 * (m_labels_latex[0] + m_labels_latex[1]);
				for(const Curve_2D* curve : m_curves)
				{
					m_ibo_size[0] += curve->m_samples * curve->m_points;
					m_ibo_size[1] += 2 * (curve->m_samples - 1) * curve->m_lines;
					m_vbo_size[0] += curve->m_samples * (curve->m_points + curve->m_lines);
				}
			}
			void Graph_2D::buffers_data(void) const
			{
				//vbo data
				vbo_data_frame();
				vbo_data_curves();
				vbo_data_tics_lines_1();
				vbo_data_tics_lines_2();
				vbo_data_label_text_1();
				vbo_data_label_text_2();
				vbo_data_label_latex_1();
				vbo_data_label_latex_2();
				vbo_data_tics_labels_1();
				vbo_data_tics_labels_2();
				//ibo data
				ibo_data_frame();
				ibo_data_tics_lines_1();
				ibo_data_tics_lines_2();
				ibo_data_label_text_1();
				ibo_data_label_text_2();
				ibo_data_curves_lines();
				ibo_data_curves_points();
				ibo_data_label_latex_1();
				ibo_data_label_latex_2();
				ibo_data_tics_labels_1();
				ibo_data_tics_labels_2();
			}

			//vbo data
			void Graph_2D::vbo_data_frame(void) const
			{
				//data
				const float w = m_width;
				const float h = m_height;
				vertices::Model3D* vbo_ptr = vbo_data_model_3D();
				//vbo data
				vbo_ptr[0].m_position = {0, 0, 0};
				vbo_ptr[1].m_position = {w, 0, 0};
				vbo_ptr[2].m_position = {w, h, 0};
				vbo_ptr[3].m_position = {0, h, 0};
				vbo_ptr[0].m_color = m_frame_color;
				vbo_ptr[1].m_color = m_frame_color;
				vbo_ptr[2].m_color = m_frame_color;
				vbo_ptr[3].m_color = m_frame_color;
			}
			void Graph_2D::vbo_data_curves(void) const
			{
				//data
				float x1, x2;
				const float w = m_width;
				const float h = m_height;
				const float a1 = m_range[2 * 0 + 0];
				const float a2 = m_range[2 * 0 + 1];
				const float b1 = m_range[2 * 1 + 0];
				const float b2 = m_range[2 * 1 + 1];
				const uint32_t n1 = m_tics_count[0];
				const uint32_t n2 = m_tics_count[1];
				vertices::Model3D* vbo_ptr = vbo_data_model_3D() + 4 * (1 + n1 + n2);
				//vbo data
				for(const Curve_2D* curve : m_curves)
				{
					if(curve->m_points)
					{
						for(uint32_t i = 0; i < curve->m_samples; i++)
						{
							curve->point(i, x1, x2);
							x1 = w * (x1 - a1) / (a2 - a1);
							x2 = h * (x2 - b1) / (b2 - b1);
							vbo_ptr[i].m_position = {x1, x2, 0};
							vbo_ptr[i].m_color = curve->m_points_color;
						}
						vbo_ptr += curve->m_samples;
					}
					if(curve->m_lines)
					{
						for(uint32_t i = 0; i < curve->m_samples; i++)
						{
							curve->point(i, x1, x2);
							x1 = w * (x1 - a1) / (a2 - a1);
							x2 = h * (x2 - b1) / (b2 - b1);
							vbo_ptr[i].m_position = {x1, x2, 0};
							vbo_ptr[i].m_color = curve->m_lines_color;
						}
						vbo_ptr += curve->m_samples;
					}
				}
			}
			void Graph_2D::vbo_data_tics_lines_1(void) const
			{
				//data
				const float w = m_width;
				const float h = m_height;
				const float s = m_tics_line_size[0];
				const uint32_t n1 = m_tics_count[0];
				vertices::Model3D* vbo_ptr = vbo_data_model_3D() + 4;
				//vbo data
				for(uint32_t i = 0; i < n1; i++)
				{
					const float x1 = w * float(i + 1) / (n1 + 1);
					vbo_ptr[4 * i + 0].m_color = m_frame_color;
					vbo_ptr[4 * i + 1].m_color = m_frame_color;
					vbo_ptr[4 * i + 2].m_color = m_frame_color;
					vbo_ptr[4 * i + 3].m_color = m_frame_color;
					vbo_ptr[4 * i + 0].m_position = {x1, 0, 0};
					vbo_ptr[4 * i + 1].m_position = {x1, h, 0};
					vbo_ptr[4 * i + 2].m_position = {x1, s, 0};
					vbo_ptr[4 * i + 3].m_position = {x1, h - s, 0};
				}
			}
			void Graph_2D::vbo_data_tics_lines_2(void) const
			{
				//data
				const float w = m_width;
				const float h = m_height;
				const float s = m_tics_line_size[1];
				const uint32_t n1 = m_tics_count[0];
				const uint32_t n2 = m_tics_count[1];
				vertices::Model3D* vbo_ptr = vbo_data_model_3D() + 4 * (1 + n1);
				//vbo data
				for(uint32_t i = 0; i < n2; i++)
				{
					const float x2 = h * float(i + 1) / (n2 + 1);
					vbo_ptr[4 * i + 0].m_color = m_frame_color;
					vbo_ptr[4 * i + 1].m_color = m_frame_color;
					vbo_ptr[4 * i + 2].m_color = m_frame_color;
					vbo_ptr[4 * i + 3].m_color = m_frame_color;
					vbo_ptr[4 * i + 0].m_position = {0, x2, 0};
					vbo_ptr[4 * i + 1].m_position = {w, x2, 0};
					vbo_ptr[4 * i + 2].m_position = {s, x2, 0};
					vbo_ptr[4 * i + 3].m_position = {w - s, x2, 0};
				}
			}
			void Graph_2D::vbo_data_label_text_1(void) const
			{
				//data
				float xc[8], tc[8];
				if(m_labels_latex[0]) return;
				const float ls = m_labels_size[0];
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t m2 = m_tics_chars[1];
				const float ts = m_tics_label_size[0];
				const Font* font = m_scene->font(m_labels_font[0]);
				const uint32_t nc = (uint32_t) strlen(m_labels_string[0]);
				vertices::Text3D* vbo_ptr = vbo_data_text_3D() + 4 * (m1 + m2);
				//vbo data
				float x1 = m_width / 2;
				float x2 = -1.5f * (ts + ls);
				for(uint32_t i = 0; i < nc; i++)
				{
					//character
					font->character(m_labels_string[0][i]).coordinates(tc);
					const int32_t w = font->character(m_labels_string[0][i]).width();
					const int32_t h = font->character(m_labels_string[0][i]).height();
					const int32_t r = font->character(m_labels_string[0][i]).advance();
					const int32_t a = font->character(m_labels_string[0][i]).bearing(0);
					const int32_t b = font->character(m_labels_string[0][i]).bearing(1);
					//position
					xc[2 * 3 + 0] = xc[2 * 0 + 0] = x1 + ls / font->height() * a;
					xc[2 * 3 + 1] = xc[2 * 2 + 1] = x2 + ls / font->height() * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = x1 + ls / font->height() * (a + w);
					xc[2 * 1 + 1] = xc[2 * 0 + 1] = x2 + ls / font->height() * (b - h);
					//vertices
					for(uint32_t j = 0; j < 4; j++)
					{
						vbo_ptr[4 * i + j].m_color = m_frame_color;
						vbo_ptr[4 * i + j].m_texture_coordinates = tc + 2 * j;
						vbo_ptr[4 * i + j].m_position = {xc[2 * j + 0], xc[2 * j + 1], 0};
					}
					x1 += ls / font->height() * r;
				}
				for(uint32_t i = 0; i < nc; i++)
				{
					for(uint32_t j = 0; j < 4; j++)
					{
						vbo_ptr[4 * i + j].m_position[0] -= x1 / 2 - m_width / 4;
					}
				}
			}
			void Graph_2D::vbo_data_label_text_2(void) const
			{
				//data
				float xc[8], tc[8];
				if(m_labels_latex[1]) return;
				const bool l1 = m_labels_latex[0];
				const float ls = m_labels_size[1];
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t m2 = m_tics_chars[1];
				const float ts = m_tics_label_size[1];
				const Font* font = m_scene->font(m_labels_font[1]);
				const uint32_t nc = (uint32_t) strlen(m_labels_string[1]);
				const uint32_t p1 = l1 ? 1 : (uint32_t) strlen(m_labels_string[0]);
				vertices::Text3D* vbo_ptr = vbo_data_text_3D() + 4 * (m1 + m2 + p1);
				//vbo data
				float h1 = 0;
				float h2 = 0;
				float x1 = 0;
				float x2 = m_height / 2;
				const uint32_t fh = font->height();
				for(uint32_t i = 0; i < nc; i++)
				{
					//character
					font->character(m_labels_string[1][i]).coordinates(tc);
					const int32_t w = font->character(m_labels_string[1][i]).width();
					const int32_t h = font->character(m_labels_string[1][i]).height();
					const int32_t r = font->character(m_labels_string[1][i]).advance();
					const int32_t a = font->character(m_labels_string[1][i]).bearing(0);
					const int32_t b = font->character(m_labels_string[1][i]).bearing(1);
					//position
					xc[2 * 3 + 0] = xc[2 * 0 + 0] = x1 + ls / fh * a;
					xc[2 * 3 + 1] = xc[2 * 2 + 1] = x2 + ls / fh * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = x1 + ls / fh * (a + w);
					xc[2 * 1 + 1] = xc[2 * 0 + 1] = x2 + ls / fh * (b - h);
					//vertices
					for(uint32_t j = 0; j < 4; j++)
					{
						vbo_ptr[4 * i + j].m_color = m_frame_color;
						vbo_ptr[4 * i + j].m_texture_coordinates = tc + 2 * j;
						vbo_ptr[4 * i + j].m_position = {xc[2 * j + 0], xc[2 * j + 1], 0};
					}
					x1 += ls / fh * r;
					h1 = std::max(h1, ls / fh * b);
					h2 = std::max(h2, ls / fh * (h - b));
				}
				for(uint32_t i = 0; i < nc; i++)
				{
					for(uint32_t j = 0; j < 4; j++)
					{
						vbo_ptr[4 * i + j].m_position[1] += (h2 - h1) / 2;
						vbo_ptr[4 * i + j].m_position[0] -= x1 + ls / fh * m_tics_width + ts;
					}
				}
			}
			void Graph_2D::vbo_data_label_latex_1(void) const
			{
				//data
				float tc[4];
				const float w = m_width;
				if(!m_labels_latex[0]) return;
				const float ls = m_labels_size[0];
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t m2 = m_tics_chars[1];
				const float ts = m_tics_label_size[0];
				const Latex* latex = m_scene->latex(m_labels_index[0]);
				const float lw = latex->width() * ls / latex->height();
				vertices::Text3D* vbo_ptr = vbo_data_text_3D() + 4 * (m1 + m2);
				//vbo data
				latex->coordinates(tc);
				vbo_ptr[0].m_color = m_frame_color;
				vbo_ptr[1].m_color = m_frame_color;
				vbo_ptr[2].m_color = m_frame_color;
				vbo_ptr[3].m_color = m_frame_color;
				vbo_ptr[0].m_texture_coordinates = {tc[0], tc[2]};
				vbo_ptr[1].m_texture_coordinates = {tc[1], tc[2]};
				vbo_ptr[2].m_texture_coordinates = {tc[1], tc[3]};
				vbo_ptr[3].m_texture_coordinates = {tc[0], tc[3]};
				vbo_ptr[0].m_position = {w / 2 - lw / 2, -1.5f * ts - 1.5f * ls};
				vbo_ptr[1].m_position = {w / 2 + lw / 2, -1.5f * ts - 1.5f * ls};
				vbo_ptr[2].m_position = {w / 2 + lw / 2, -1.5f * ts - 0.5f * ls};
				vbo_ptr[3].m_position = {w / 2 - lw / 2, -1.5f * ts - 0.5f * ls};
			}
			void Graph_2D::vbo_data_label_latex_2(void) const
			{
				//data
				float tc[4];
				const float h = m_height;
				if(!m_labels_latex[1]) return;
				const bool l1 = m_labels_latex[0];
				const float ls = m_labels_size[1];
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t m2 = m_tics_chars[1];
				const float ts = m_tics_label_size[1];
				const Font* font = m_scene->font(m_tics_font[1]);
				const Latex* latex = m_scene->latex(m_labels_index[1]);
				const float lw = latex->width() * ls / latex->height();
				const uint32_t p1 = l1 ? 1 : (uint32_t) strlen(m_labels_string[0]);
				vertices::Text3D* vbo_ptr = vbo_data_text_3D() + 4 * (m1 + m2 + p1);
				const float x1 = -ts * m_tics_width / font->height() - ts / 2 - lw - ls / 2;
				//vbo data
				latex->coordinates(tc);
				vbo_ptr[0].m_color = m_frame_color;
				vbo_ptr[1].m_color = m_frame_color;
				vbo_ptr[2].m_color = m_frame_color;
				vbo_ptr[3].m_color = m_frame_color;
				vbo_ptr[0].m_position = {x1, h / 2 - ls / 2};
				vbo_ptr[3].m_position = {x1, h / 2 + ls / 2};
				vbo_ptr[1].m_position = {x1 + lw, h / 2 - ls / 2};
				vbo_ptr[2].m_position = {x1 + lw, h / 2 + ls / 2};
				vbo_ptr[0].m_texture_coordinates = {tc[0], tc[2]};
				vbo_ptr[1].m_texture_coordinates = {tc[1], tc[2]};
				vbo_ptr[2].m_texture_coordinates = {tc[1], tc[3]};
				vbo_ptr[3].m_texture_coordinates = {tc[0], tc[3]};
			}
			void Graph_2D::vbo_data_tics_labels_1(void) const
			{
				//data
				char label[20];
				float xc[8], tc[8];
				const float w = m_width;
				const uint32_t nt = m_tics_count[0];
				const float z1 = m_range[2 * 0 + 0];
				const float z2 = m_range[2 * 0 + 1];
				const float sl = m_tics_label_size[0];
				vertices::Text3D* vbo_ptr = vbo_data_text_3D();
				const Font* font = m_scene->font(m_tics_font[0]);
				//vbo data
				uint32_t counter = 0;
				const uint32_t fh = font->height();
				for(uint32_t i = 0; i < nt + 2; i++)
				{
					float sw = 0;
					float x2 = -1.5f * sl;
					float x1 = w * float(i) / (nt + 1);
					const float zi = z1 + i * (z2 - z1) / (nt + 1);
					uint32_t nc = sprintf(label, m_tics_format[0], zi);
					for(uint32_t j = 0; j < nc; j++)
					{
						//character
						font->character(label[j]).coordinates(tc);
						const int32_t w = font->character(label[j]).width();
						const int32_t h = font->character(label[j]).height();
						const int32_t r = font->character(label[j]).advance();
						const int32_t a = font->character(label[j]).bearing(0);
						const int32_t b = font->character(label[j]).bearing(1);
						//position
						xc[2 * 3 + 0] = xc[2 * 0 + 0] = x1 + sl / fh * a;
						xc[2 * 3 + 1] = xc[2 * 2 + 1] = x2 + sl / fh * b;
						xc[2 * 1 + 0] = xc[2 * 2 + 0] = x1 + sl / fh * (a + w);
						xc[2 * 1 + 1] = xc[2 * 0 + 1] = x2 + sl / fh * (b - h);
						//vertices
						for(uint32_t k = 0; k < 4; k++)
						{
							vbo_ptr[4 * counter + k].m_color = m_frame_color;
							vbo_ptr[4 * counter + k].m_texture_coordinates = tc + 2 * k;
							vbo_ptr[4 * counter + k].m_position = {xc[2 * k + 0], xc[2 * k + 1], 0};
						}
						counter++;
						x1 += sl / fh * r;
						sw += sl / fh * r;
					}
					for(uint32_t j = 0; j < nc; j++)
					{
						for(uint32_t k = 0; k < 4; k++)
						{
							vbo_ptr[4 * (counter - nc + j) + k].m_position[0] -= sw / 2;
						}
					}
				}
			}
			void Graph_2D::vbo_data_tics_labels_2(void) const
			{
				//data
				char label[20];
				float xc[8], tc[8];
				const float h = m_height;
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t nt = m_tics_count[1];
				const float z1 = m_range[2 * 1 + 0];
				const float z2 = m_range[2 * 1 + 1];
				const float sl = m_tics_label_size[1];
				const Font* font = m_scene->font(m_tics_font[1]);
				vertices::Text3D* vbo_ptr = vbo_data_text_3D() + 4 * m1;
				//vbo data
				uint32_t counter = 0;
				const uint32_t fh = font->height();
				for(uint32_t i = 0; i < nt + 2; i++)
				{
					float h1 = 0;
					float h2 = 0;
					float x1 = 0;
					float x2 = h * float(i) / (nt + 1);
					const float zi = z1 + i * (z2 - z1) / (nt + 1);
					uint32_t nc = sprintf(label, m_tics_format[1], zi);
					for(uint32_t j = 0; j < nc; j++)
					{
						//character
						font->character(label[j]).coordinates(tc);
						const int32_t w = font->character(label[j]).width();
						const int32_t h = font->character(label[j]).height();
						const int32_t r = font->character(label[j]).advance();
						const int32_t a = font->character(label[j]).bearing(0);
						const int32_t b = font->character(label[j]).bearing(1);
						//position
						xc[2 * 3 + 0] = xc[2 * 0 + 0] = x1 + sl / fh * a;
						xc[2 * 3 + 1] = xc[2 * 2 + 1] = x2 + sl / fh * b;
						xc[2 * 1 + 0] = xc[2 * 2 + 0] = x1 + sl / fh * (a + w);
						xc[2 * 1 + 1] = xc[2 * 0 + 1] = x2 + sl / fh * (b - h);
						//vertices
						for(uint32_t k = 0; k < 4; k++)
						{
							vbo_ptr[4 * counter + k].m_color = m_frame_color;
							vbo_ptr[4 * counter + k].m_texture_coordinates = tc + 2 * k;
							vbo_ptr[4 * counter + k].m_position = {xc[2 * k + 0], xc[2 * k + 1], 0};
						}
						counter++;
						x1 += sl / fh * r;
						h1 = std::max(h1, sl / fh * b);
						h2 = std::max(h2, sl / fh * (h - b));
					}
					for(uint32_t j = 0; j < nc; j++)
					{
						for(uint32_t k = 0; k < 4; k++)
						{
							vbo_ptr[4 * (counter - nc + j) + k].m_position[0] -= x1 + sl / 2;
							vbo_ptr[4 * (counter - nc + j) + k].m_position[1] += (h2 - h1) / 2;
						}
					}
				}
			}

			//ibo data
			void Graph_2D::ibo_data_frame(void) const
			{
				//data
				uint32_t* ibo_ptr = ibo_data(1);
				//ibo data
				ibo_ptr[2 * 0 + 0] = m_vbo_index[0] + 0;
				ibo_ptr[2 * 0 + 1] = m_vbo_index[0] + 1;
				ibo_ptr[2 * 1 + 0] = m_vbo_index[0] + 1;
				ibo_ptr[2 * 1 + 1] = m_vbo_index[0] + 2;
				ibo_ptr[2 * 2 + 0] = m_vbo_index[0] + 2;
				ibo_ptr[2 * 2 + 1] = m_vbo_index[0] + 3;
				ibo_ptr[2 * 3 + 0] = m_vbo_index[0] + 3;
				ibo_ptr[2 * 3 + 1] = m_vbo_index[0] + 0;
			}
			void Graph_2D::ibo_data_tics_lines_1(void) const
			{
				//data
				uint32_t* ibo_ptr = ibo_data(1) + 8;
				const uint32_t n1 = m_tics_count[0];
				const uint32_t vbo_index = m_vbo_index[0] + 4;
				//ibo data
				for(uint32_t i = 0; i < n1; i++)
				{
					ibo_ptr[4 * i + 0] = vbo_index + 4 * i + 0;
					ibo_ptr[4 * i + 1] = vbo_index + 4 * i + 2;
					ibo_ptr[4 * i + 2] = vbo_index + 4 * i + 1;
					ibo_ptr[4 * i + 3] = vbo_index + 4 * i + 3;
				}
			}
			void Graph_2D::ibo_data_tics_lines_2(void) const
			{
				//data
				const uint32_t n1 = m_tics_count[0];
				const uint32_t n2 = m_tics_count[1];
				uint32_t* ibo_ptr = ibo_data(1) + 4 * (2 + n1);
				const uint32_t vbo_index = m_vbo_index[0] + 4 * (1 + n1);
				//ibo data
				for(uint32_t i = 0; i < n2; i++)
				{
					ibo_ptr[4 * i + 0] = vbo_index + 4 * i + 0;
					ibo_ptr[4 * i + 1] = vbo_index + 4 * i + 2;
					ibo_ptr[4 * i + 2] = vbo_index + 4 * i + 1;
					ibo_ptr[4 * i + 3] = vbo_index + 4 * i + 3;
				}
			}
			void Graph_2D::ibo_data_label_text_1(void) const
			{
				//data
				if(m_labels_latex[0]) return;
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t m2 = m_tics_chars[1];
				uint32_t* ibo_ptr = ibo_data(4) + 6 * (m1 + m2);
				const uint32_t nc = (uint32_t) strlen(m_labels_string[0]);
				const uint32_t vbo_index = m_vbo_index[2] + 4 * (m1 + m2);
				//ibo data
				for(uint32_t i = 0; i < nc; i++)
				{
					ibo_ptr[6 * i + 3 * 0 + 0] = vbo_index + 4 * i + 0;
					ibo_ptr[6 * i + 3 * 0 + 1] = vbo_index + 4 * i + 1;
					ibo_ptr[6 * i + 3 * 0 + 2] = vbo_index + 4 * i + 2;
					ibo_ptr[6 * i + 3 * 1 + 0] = vbo_index + 4 * i + 0;
					ibo_ptr[6 * i + 3 * 1 + 1] = vbo_index + 4 * i + 2;
					ibo_ptr[6 * i + 3 * 1 + 2] = vbo_index + 4 * i + 3;
				}
			}
			void Graph_2D::ibo_data_label_text_2(void) const
			{
				//data
				if(m_labels_latex[1]) return;
				uint32_t* ibo_ptr = ibo_data(4);
				const bool l1 = m_labels_latex[0];
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t m2 = m_tics_chars[1];
				const uint32_t nc = (uint32_t) strlen(m_labels_string[1]);
				const uint32_t p1 = l1 ? 1 : (uint32_t) strlen(m_labels_string[0]);
				const uint32_t q1 = l1 ? 0 : (uint32_t) strlen(m_labels_string[0]);
				const uint32_t vbo_index = m_vbo_index[2] + 4 * (m1 + m2 + p1);
				//ibo data
				ibo_ptr += 6 * (m1 + m2 + q1);
				for(uint32_t i = 0; i < nc; i++)
				{
					ibo_ptr[6 * i + 3 * 0 + 0] = vbo_index + 4 * i + 0;
					ibo_ptr[6 * i + 3 * 0 + 1] = vbo_index + 4 * i + 1;
					ibo_ptr[6 * i + 3 * 0 + 2] = vbo_index + 4 * i + 2;
					ibo_ptr[6 * i + 3 * 1 + 0] = vbo_index + 4 * i + 0;
					ibo_ptr[6 * i + 3 * 1 + 1] = vbo_index + 4 * i + 2;
					ibo_ptr[6 * i + 3 * 1 + 2] = vbo_index + 4 * i + 3;
				}
			}
			void Graph_2D::ibo_data_curves_lines(void) const
			{
				//data
				const uint32_t n1 = m_tics_count[0];
				const uint32_t n2 = m_tics_count[1];
				uint32_t* ibo_ptr = ibo_data(1) + 4 * (2 + n1 + n2);
				uint32_t vbo_index = m_vbo_index[0] + 4 * (1 + n1 + n2);
				//ibo data
				for(const Curve_2D* curve : m_curves)
				{
					if(curve->m_points) vbo_index += curve->m_samples;
					if(curve->m_lines)
					{
						for(uint32_t i = 0; i < curve->m_samples - 1; i++)
						{
							ibo_ptr[2 * i + 0] = vbo_index + i + 0;
							ibo_ptr[2 * i + 1] = vbo_index + i + 1;
						}
						vbo_index += curve->m_samples;
						ibo_ptr += 2 * (curve->m_samples - 1);
					}
				}
			}
			void Graph_2D::ibo_data_curves_points(void) const
			{
				//data
				uint32_t* ibo_ptr = ibo_data(0);
				const uint32_t n1 = m_tics_count[0];
				const uint32_t n2 = m_tics_count[1];
				uint32_t vbo_index = m_vbo_index[0] + 4 * (1 + n1 + n2);
				//ibo data
				for(const Curve_2D* curve : m_curves)
				{
					if(curve->m_points)
					{
						for(uint32_t i = 0; i < curve->m_samples; i++)
						{
							ibo_ptr[i] = vbo_index + i;
						}
					}
					ibo_ptr += curve->m_samples;
					vbo_index += curve->m_samples;
					if(curve->m_lines) vbo_index += curve->m_samples;
				}
			}
			void Graph_2D::ibo_data_label_latex_1(void) const
			{
				//data
				if(!m_labels_latex[0]) return;
				uint32_t* ibo_ptr = ibo_data(5);
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t m2 = m_tics_chars[1];
				const uint32_t vbo_index = m_vbo_index[2] + 4 * (m1 + m2);
				//ibo data
				ibo_ptr[3 * 0 + 0] = vbo_index + 0;
				ibo_ptr[3 * 0 + 1] = vbo_index + 1;
				ibo_ptr[3 * 0 + 2] = vbo_index + 2;
				ibo_ptr[3 * 1 + 0] = vbo_index + 0;
				ibo_ptr[3 * 1 + 1] = vbo_index + 2;
				ibo_ptr[3 * 1 + 2] = vbo_index + 3;
			}
			void Graph_2D::ibo_data_label_latex_2(void) const
			{
				//data
				if(!m_labels_latex[1]) return;
				uint32_t* ibo_ptr = ibo_data(5);
				const bool l1 = m_labels_latex[0];
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t m2 = m_tics_chars[1];
				const uint32_t p1 = l1 ? 1 : (uint32_t) strlen(m_labels_string[0]);
				const uint32_t vbo_index = m_vbo_index[2] + 4 * (m1 + m2 + p1);
				//ibo data
				ibo_ptr += 6 * l1;
				ibo_ptr[3 * 0 + 0] = vbo_index + 0;
				ibo_ptr[3 * 0 + 1] = vbo_index + 1;
				ibo_ptr[3 * 0 + 2] = vbo_index + 2;
				ibo_ptr[3 * 1 + 0] = vbo_index + 0;
				ibo_ptr[3 * 1 + 1] = vbo_index + 2;
				ibo_ptr[3 * 1 + 2] = vbo_index + 3;
			}
			void Graph_2D::ibo_data_tics_labels_1(void) const
			{
				//data
				char label[20];
				uint32_t* ibo_ptr = ibo_data(4);
				const uint32_t nt = m_tics_count[0];
				const float z1 = m_range[2 * 0 + 0];
				const float z2 = m_range[2 * 0 + 1];
				//ibo data
				uint32_t counter = 0;
				for(uint32_t i = 0; i < nt + 2; i++)
				{
					const float zi = z1 + i * (z2 - z1) / (nt + 1);
					uint32_t nc = sprintf(label, m_tics_format[0], zi);
					for(uint32_t j = 0; j < nc; j++)
					{
						ibo_ptr[6 * counter + 3 * 0 + 0] = m_vbo_index[2] + 4 * counter + 0;
						ibo_ptr[6 * counter + 3 * 0 + 1] = m_vbo_index[2] + 4 * counter + 1;
						ibo_ptr[6 * counter + 3 * 0 + 2] = m_vbo_index[2] + 4 * counter + 2;
						ibo_ptr[6 * counter + 3 * 1 + 0] = m_vbo_index[2] + 4 * counter + 0;
						ibo_ptr[6 * counter + 3 * 1 + 1] = m_vbo_index[2] + 4 * counter + 2;
						ibo_ptr[6 * counter + 3 * 1 + 2] = m_vbo_index[2] + 4 * counter + 3;
						counter++;
					}
				}
			}
			void Graph_2D::ibo_data_tics_labels_2(void) const
			{
				//data
				char label[20];
				const uint32_t m1 = m_tics_chars[0];
				const uint32_t nt = m_tics_count[1];
				const float z1 = m_range[2 * 1 + 0];
				const float z2 = m_range[2 * 1 + 1];
				uint32_t* ibo_ptr = ibo_data(4) + 6 * m1;
				uint32_t vbo_index = m_vbo_index[2] + 4 * m1;
				//ibo data
				uint32_t counter = 0;
				for(uint32_t i = 0; i < nt + 2; i++)
				{
					const float zi = z1 + i * (z2 - z1) / (nt + 1);
					uint32_t nc = sprintf(label, m_tics_format[1], zi);
					for(uint32_t j = 0; j < nc; j++)
					{
						ibo_ptr[6 * counter + 3 * 0 + 0] = vbo_index + 4 * counter + 0;
						ibo_ptr[6 * counter + 3 * 0 + 1] = vbo_index + 4 * counter + 1;
						ibo_ptr[6 * counter + 3 * 0 + 2] = vbo_index + 4 * counter + 2;
						ibo_ptr[6 * counter + 3 * 1 + 0] = vbo_index + 4 * counter + 0;
						ibo_ptr[6 * counter + 3 * 1 + 1] = vbo_index + 4 * counter + 2;
						ibo_ptr[6 * counter + 3 * 1 + 2] = vbo_index + 4 * counter + 3;
						counter++;
					}
				}
			}
		}
	}
}