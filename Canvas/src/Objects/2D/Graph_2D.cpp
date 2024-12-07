#pragma once

//canvas
#include "Canvas/Canvas/inc/Scene/Font.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Graph_2D.hpp"

//static data
static uint32_t counter;

namespace canvas
{
	namespace objects
	{
		//constructors
		Graph_2D::Graph_2D(void) : 
			m_range{0, 1, 0, 1}, 
			m_labels_latex{false, false}, m_labels_size{0.04f, 0.04f}, m_labels_font{0, 0}, 
			m_labels_index{0, 0}, m_labels_string{"x1", "x2"},
			m_tics_font{0, 0}, m_tics_count{9, 9}, m_tics_format{"%.2f", "%.2f"}, 
			m_tics_line_size{0.02f, 0.02f}, m_tics_label_size{0.04f, 0.04f}
		{
			return;
		}

		//destructor
		Graph_2D::~Graph_2D(void)
		{
			return;
		}

		//data
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

		float Graph_2D::tics_line_size(uint32_t index) const
		{
			return m_tics_line_size[index];
		}
		float Graph_2D::tics_line_size(uint32_t index, float size)
		{
			return m_tics_line_size[index] = size;
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

		const char* Graph_2D::tics_format(uint32_t index) const
		{
			return m_tics_format[index];
		}
		const char* Graph_2D::tics_format(uint32_t index, const char* format)
		{
			return strcpy(m_tics_format[index], format);
		}

		//buffers
		void Graph_2D::buffers_size(void)
		{
			//data
			int32_t nc;
			char label[20];
			const uint32_t n1 = m_tics_count[0];
			const uint32_t n2 = m_tics_count[1];
			const float x11 = m_range[2 * 0 + 0];
			const float x12 = m_range[2 * 0 + 1];
			const float x21 = m_range[2 * 1 + 0];
			const float x22 = m_range[2 * 1 + 1];
			//sizes
			m_vbo_size[0] = 4 * (1 + n1 + n2);
			m_ibo_size[1] = 4 * (2 + n1 + n2);
			//tics labels
			m_vbo_size[2] = 0;
			m_ibo_size[4] = 0;
			for(uint32_t i = 0; i < n1 + 2; i++)
			{
				nc = sprintf(label, m_tics_format[0], x11 + i * (x12 - x11) / (n1 + 1));
				if(nc < 0) {fprintf(stderr, "Error: Graph2D invalid format!\n"); exit(EXIT_FAILURE); }
				m_vbo_size[2] += 4 * nc;
				m_ibo_size[4] += 6 * nc;
			}
			for(uint32_t i = 0; i < n2 + 2; i++)
			{
				nc = sprintf(label, m_tics_format[1], x21 + i * (x22 - x21) / (n2 + 1));
				if(nc < 0) {fprintf(stderr, "Error: Graph2D invalid format!\n"); exit(EXIT_FAILURE); }
				m_vbo_size[2] += 4 * nc;
				m_ibo_size[4] += 6 * nc;
			}
			//labels
			m_ibo_size[5] += 6 * (m_labels_latex[0] ? 1 : 0);
			m_ibo_size[5] += 6 * (m_labels_latex[1] ? 1 : 0);
			m_vbo_size[2] += 4 * (m_labels_latex[0] ? 1 : (uint32_t) strlen(m_labels_string[0]));
			m_vbo_size[2] += 4 * (m_labels_latex[1] ? 1 : (uint32_t) strlen(m_labels_string[1]));
			m_ibo_size[4] += 6 * (!m_labels_latex[0] ? (uint32_t) strlen(m_labels_string[0]) : 0);
			m_ibo_size[4] += 6 * (!m_labels_latex[1] ? (uint32_t) strlen(m_labels_string[1]) : 0);
		}
		void Graph_2D::buffers_data(void) const
		{
			//vbo data
			counter = 0;
			vbo_data_frame();
			vbo_data_tics_lines();
			vbo_data_label_text_1();
			vbo_data_label_text_2();
			vbo_data_label_latex_1();
			vbo_data_label_latex_2();
			vbo_data_tics_labels_1();
			vbo_data_tics_labels_2();
			//ibo data
			counter = 0;
			ibo_data_frame();
			ibo_data_tics_lines();
			ibo_data_label_text_1();
			ibo_data_label_text_2();
			ibo_data_label_latex_1();
			ibo_data_label_latex_2();
			ibo_data_tics_labels_1();
			ibo_data_tics_labels_2();
		}

		//vbo data
		void Graph_2D::vbo_data_frame(void) const
		{
			//data
			vertices::Model3D* vbo_ptr = vbo_data_model_3D();
			//vbo data
			vbo_ptr[0].m_position = {0, 0, 0};
			vbo_ptr[1].m_position = {1, 0, 0};
			vbo_ptr[2].m_position = {1, 1, 0};
			vbo_ptr[3].m_position = {0, 1, 0};
			vbo_ptr[0].m_color = m_frame_color;
			vbo_ptr[1].m_color = m_frame_color;
			vbo_ptr[2].m_color = m_frame_color;
			vbo_ptr[3].m_color = m_frame_color;
		}
		void Graph_2D::vbo_data_label_text_1(void) const
		{
			//data
			float xc[8], tc[8];
			if(m_labels_latex[0]) return;
			const float ls = m_labels_size[0];
			const float ts = m_tics_label_size[0];
			vertices::Text3D* vbo_ptr = vbo_data_text_3D();
			const Font* font = m_scene->font(m_labels_font[0]);
			const uint32_t nc = (uint32_t) strlen(m_labels_string[0]);
			//vbo data
			float w1 = 0.5f;
			float w2 = -1.5f * (ts + ls);
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
				xc[2 * 3 + 0] = xc[2 * 0 + 0] = w1 + ls / font->height() * a;
				xc[2 * 3 + 1] = xc[2 * 2 + 1] = w2 + ls / font->height() * b;
				xc[2 * 1 + 0] = xc[2 * 2 + 0] = w1 + ls / font->height() * (a + w);
				xc[2 * 1 + 1] = xc[2 * 0 + 1] = w2 + ls / font->height() * (b - h);
				//vertices
				for(uint32_t j = 0; j < 4; j++)
				{
					vbo_ptr[4 * counter + j].m_color = m_frame_color;
					vbo_ptr[4 * counter + j].m_texture_coordinates = tc + 2 * j;
					vbo_ptr[4 * counter + j].m_position = {xc[2 * j + 0], xc[2 * j + 1], 0};
				}
				counter++;
				w1 += ls / font->height() * r;
			}
			for(uint32_t i = 0; i < nc; i++)
			{
				for(uint32_t j = 0; j < 4; j++)
				{
					vbo_ptr[4 * (counter - nc + i) + j].m_position[0] -= (w1 - 0.5f) / 2;
				}
			}
		}
		void Graph_2D::vbo_data_label_text_2(void) const
		{
			//data
			float xc[8], tc[8];
			if(m_labels_latex[1]) return;
			const float ls = m_labels_size[1];
			vertices::Text3D* vbo_ptr = vbo_data_text_3D();
			const Font* font = m_scene->font(m_labels_font[1]);
			const uint32_t nc = (uint32_t) strlen(m_labels_string[1]);
			//vbo data
			float w1 = 0;
			float w2 = 0.5f;
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
				xc[2 * 3 + 0] = xc[2 * 0 + 0] = w1 + ls / font->height() * a;
				xc[2 * 3 + 1] = xc[2 * 2 + 1] = w2 + ls / font->height() * b;
				xc[2 * 1 + 0] = xc[2 * 2 + 0] = w1 + ls / font->height() * (a + w);
				xc[2 * 1 + 1] = xc[2 * 0 + 1] = w2 + ls / font->height() * (b - h);
				//vertices
				for(uint32_t j = 0; j < 4; j++)
				{
					vbo_ptr[4 * counter + j].m_color = m_frame_color;
					vbo_ptr[4 * counter + j].m_texture_coordinates = tc + 2 * j;
					vbo_ptr[4 * counter + j].m_position = {xc[2 * j + 0], xc[2 * j + 1], 0};
				}
				counter++;
				w1 += ls / font->height() * r;
			}
			// for(uint32_t i = 0; i < nc; i++)
			// {
			// 	for(uint32_t j = 0; j < 4; j++)
			// 	{
			// 		vbo_ptr[4 * (counter - nc + i) + j].m_position[0] -= (w1 - 0.5f) / 2;
			// 	}
			// }
		}
		void Graph_2D::vbo_data_label_latex_1(void) const
		{
			//data
			//check
			if(!m_labels_latex[0]) return;
		}
		void Graph_2D::vbo_data_label_latex_2(void) const
		{
			//data
			//check
			if(!m_labels_latex[1]) return;
			//vbo data
		}
		void Graph_2D::vbo_data_tics_lines(void) const
		{
			//data
			const uint32_t n1 = m_tics_count[0];
			const uint32_t n2 = m_tics_count[1];
			const float s1 = m_tics_line_size[0];
			const float s2 = m_tics_line_size[1];
			vertices::Model3D* vbo_ptr = vbo_data_model_3D() + 4;
			//vbo data
			for(uint32_t i = 0; i < n1; i++)
			{
				const float x1 = float(i + 1) / (n1 + 1);
				vbo_ptr[2 * (0 * n1 + 0 * n2) + 2 * i + 0].m_color = m_frame_color;
				vbo_ptr[2 * (0 * n1 + 0 * n2) + 2 * i + 1].m_color = m_frame_color;
				vbo_ptr[2 * (1 * n1 + 1 * n2) + 2 * i + 0].m_color = m_frame_color;
				vbo_ptr[2 * (1 * n1 + 1 * n2) + 2 * i + 1].m_color = m_frame_color;
				vbo_ptr[2 * (0 * n1 + 0 * n2) + 2 * i + 0].m_position = {x1, 0, 0};
				vbo_ptr[2 * (1 * n1 + 1 * n2) + 2 * i + 0].m_position = {x1, 1, 0};
				vbo_ptr[2 * (0 * n1 + 0 * n2) + 2 * i + 1].m_position = {x1, s1, 0};
				vbo_ptr[2 * (1 * n1 + 1 * n2) + 2 * i + 1].m_position = {x1, 1 - s1, 0};
			}
			for(uint32_t i = 0; i < n2; i++)
			{
				const float x2 = float(i + 1) / (n2 + 1);
				vbo_ptr[2 * (1 * n1 + 0 * n2) + 2 * i + 0].m_color = m_frame_color;
				vbo_ptr[2 * (1 * n1 + 0 * n2) + 2 * i + 1].m_color = m_frame_color;
				vbo_ptr[2 * (2 * n1 + 1 * n2) + 2 * i + 0].m_color = m_frame_color;
				vbo_ptr[2 * (2 * n1 + 1 * n2) + 2 * i + 1].m_color = m_frame_color;
				vbo_ptr[2 * (1 * n1 + 0 * n2) + 2 * i + 0].m_position = {1, x2, 0};
				vbo_ptr[2 * (2 * n1 + 1 * n2) + 2 * i + 0].m_position = {0, x2, 0};
				vbo_ptr[2 * (2 * n1 + 1 * n2) + 2 * i + 1].m_position = {s2, x2, 0};
				vbo_ptr[2 * (1 * n1 + 0 * n2) + 2 * i + 1].m_position = {1 - s2, x2, 0};
			}
		}
		void Graph_2D::vbo_data_tics_labels_1(void) const
		{
			//data
			char label[20];
			float xc[8], tc[8];
			const uint32_t nt = m_tics_count[0];
			const float z1 = m_range[2 * 0 + 0];
			const float z2 = m_range[2 * 0 + 1];
			const float sl = m_tics_label_size[0];
			vertices::Text3D* vbo_ptr = vbo_data_text_3D();
			const Font* font = m_scene->font(m_tics_font[0]);
			//vbo data
			for(uint32_t i = 0; i < nt + 2; i++)
			{
				float sw = 0;
				float w2 = -1.5f * sl;
				float w1 = float(i) / (nt + 1);
				const float x1 = z1 + i * (z2 - z1) / (nt + 1);
				uint32_t nc = sprintf(label, m_tics_format[0], x1);
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
					xc[2 * 3 + 0] = xc[2 * 0 + 0] = w1 + sl / font->height() * a;
					xc[2 * 3 + 1] = xc[2 * 2 + 1] = w2 + sl / font->height() * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = w1 + sl / font->height() * (a + w);
					xc[2 * 1 + 1] = xc[2 * 0 + 1] = w2 + sl / font->height() * (b - h);
					//vertices
					for(uint32_t k = 0; k < 4; k++)
					{
						vbo_ptr[4 * counter + k].m_color = m_frame_color;
						vbo_ptr[4 * counter + k].m_texture_coordinates = tc + 2 * k;
						vbo_ptr[4 * counter + k].m_position = {xc[2 * k + 0], xc[2 * k + 1], 0};
					}
					counter++;
					w1 += sl / font->height() * r;
					sw += sl / font->height() * r;
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
			const uint32_t nt = m_tics_count[1];
			const float z1 = m_range[2 * 1 + 0];
			const float z2 = m_range[2 * 1 + 1];
			const float sl = m_tics_label_size[1];
			vertices::Text3D* vbo_ptr = vbo_data_text_3D();
			const Font* font = m_scene->font(m_tics_font[1]);
			//vbo data
			for(uint32_t i = 0; i < nt + 2; i++)
			{
				float h1 = 0;
				float h2 = 0;
				float w1 = 0;
				float w2 = float(i) / (nt + 1) - 0 * sl / 2;
				const float x2 = z1 + i * (z2 - z1) / (nt + 1);
				uint32_t nc = sprintf(label, m_tics_format[1], x2);
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
					xc[2 * 3 + 0] = xc[2 * 0 + 0] = w1 + sl / font->height() * a;
					xc[2 * 3 + 1] = xc[2 * 2 + 1] = w2 + sl / font->height() * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = w1 + sl / font->height() * (a + w);
					xc[2 * 1 + 1] = xc[2 * 0 + 1] = w2 + sl / font->height() * (b - h);
					//vertices
					for(uint32_t k = 0; k < 4; k++)
					{
						vbo_ptr[4 * counter + k].m_color = m_frame_color;
						vbo_ptr[4 * counter + k].m_texture_coordinates = tc + 2 * k;
						vbo_ptr[4 * counter + k].m_position = {xc[2 * k + 0], xc[2 * k + 1], 0};
					}
					counter++;
					w1 += sl / font->height() * r;
					h1 = std::max(h1, sl / font->height() * b);
					h2 = std::max(h2, sl / font->height() * (h - b));
				}
				for(uint32_t j = 0; j < nc; j++)
				{
					for(uint32_t k = 0; k < 4; k++)
					{
						vbo_ptr[4 * (counter - nc + j) + k].m_position[1] += (h2 - h1) / 2;
						vbo_ptr[4 * (counter - nc + j) + k].m_position[0] -= w1 + 0.5f * sl;
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
		void Graph_2D::ibo_data_tics_lines(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(1) + 8;
			const uint32_t n1 = m_tics_count[0];
			const uint32_t n2 = m_tics_count[1];
			//ibo data
			for(uint32_t i = 0; i < n1; i++)
			{
				const uint32_t a = m_vbo_index[0] + 4 + 2 * i;
				ibo_ptr[2 * (0 * n1 + 0 * n2) + 2 * i + 0] = a + 2 * (0 * n1 + 0 * n2) + 0;
				ibo_ptr[2 * (0 * n1 + 0 * n2) + 2 * i + 1] = a + 2 * (0 * n1 + 0 * n2) + 1;
				ibo_ptr[2 * (1 * n1 + 1 * n2) + 2 * i + 0] = a + 2 * (1 * n1 + 1 * n2) + 0;
				ibo_ptr[2 * (1 * n1 + 1 * n2) + 2 * i + 1] = a + 2 * (1 * n1 + 1 * n2) + 1;
			}
			for(uint32_t i = 0; i < n2; i++)
			{
				const uint32_t a = m_vbo_index[0] + 4 + 2 * i;
				ibo_ptr[2 * (1 * n1 + 0 * n2) + 2 * i + 0] = a + 2 * (1 * n1 + 0 * n2) + 0;
				ibo_ptr[2 * (1 * n1 + 0 * n2) + 2 * i + 1] = a + 2 * (1 * n1 + 0 * n2) + 1;
				ibo_ptr[2 * (2 * n1 + 1 * n2) + 2 * i + 0] = a + 2 * (2 * n1 + 1 * n2) + 0;
				ibo_ptr[2 * (2 * n1 + 1 * n2) + 2 * i + 1] = a + 2 * (2 * n1 + 1 * n2) + 1;
			}
		}
		void Graph_2D::ibo_data_label_text_1(void) const
		{
			//data
			if(m_labels_latex[0]) return;
			uint32_t* ibo_ptr = ibo_data(4);
			const uint32_t nc = (uint32_t) strlen(m_labels_string[0]);
			//ibo data
			for(uint32_t i = 0; i < nc; i++)
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
		void Graph_2D::ibo_data_label_text_2(void) const
		{
			//data
			if(m_labels_latex[1]) return;
			uint32_t* ibo_ptr = ibo_data(4);
			const uint32_t nc = (uint32_t) strlen(m_labels_string[1]);
			//ibo data
			for(uint32_t i = 0; i < nc; i++)
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
		void Graph_2D::ibo_data_label_latex_1(void) const
		{

		}
		void Graph_2D::ibo_data_label_latex_2(void) const
		{

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
			for(uint32_t i = 0; i < nt + 2; i++)
			{
				const float x1 = z1 + i * (z2 - z1) / (nt + 1);
				uint32_t nc = sprintf(label, m_tics_format[0], x1);
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
			uint32_t* ibo_ptr = ibo_data(4);
			const uint32_t nt = m_tics_count[1];
			const float z1 = m_range[2 * 1 + 0];
			const float z2 = m_range[2 * 1 + 1];
			//ibo data
			for(uint32_t i = 0; i < nt + 2; i++)
			{
				const float x2 = z1 + i * (z2 - z1) / (nt + 1);
				uint32_t nc = sprintf(label, m_tics_format[1], x2);
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
	}
}