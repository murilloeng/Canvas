#pragma once

//canvas
#include "Canvas/Canvas/inc/Scene/Font.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Graph_2D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Graph_2D::Graph_2D(void) : 
			m_range{0, 1, 0, 1}, 
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
			const uint32_t n1 = m_tics_count[0];
			const uint32_t n2 = m_tics_count[1];
			const float x11 = m_range[2 * 0 + 0];
			const float x12 = m_range[2 * 0 + 1];
			const float x21 = m_range[2 * 1 + 0];
			const float x22 = m_range[2 * 1 + 1];
			//sizes
			char label[20];
			m_vbo_size[2] = 0;
			m_ibo_size[4] = 0;
			m_vbo_size[0] = 4 * (1 + n1 + n2);
			m_ibo_size[1] = 4 * (2 + n1 + n2);
			for(uint32_t i = 0; i < n1 + 2; i++)
			{
				nc = sprintf(label, m_tics_format[0], x11 + i * (x12 - x11) / (n1 + 1));
				if(nc < 0) {fprintf(stderr, "Error: Graph 2D has an invalid format!\n"); exit(EXIT_FAILURE); }
				m_vbo_size[2] += 4 * nc;
				m_ibo_size[4] += 6 * nc;
			}
			for(uint32_t i = 0; i < n2 + 2; i++)
			{
				nc = sprintf(label, m_tics_format[1], x21 + i * (x22 - x21) / (n2 + 1));
				if(nc < 0) {fprintf(stderr, "Error: Graph 2D has an invalid format!\n"); exit(EXIT_FAILURE); }
				m_vbo_size[2] += 4 * nc;
				m_ibo_size[4] += 6 * nc;
			}
		}
		void Graph_2D::buffers_data(void) const
		{
			buffers_data_tics();
			buffers_data_frame();
			buffers_data_labels();
		}

		//buffers
		void Graph_2D::buffers_data_tics(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(1) + 8;
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
		void Graph_2D::buffers_data_frame(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(1);
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
		void Graph_2D::buffers_data_labels(void) const
		{
			//data
			char label[20];
			float xc[8], tc[8];
			uint32_t* ibo_ptr = ibo_data(4);
			const uint32_t n1 = m_tics_count[0];
			const uint32_t n2 = m_tics_count[1];
			const float x11 = m_range[2 * 0 + 0];
			const float x12 = m_range[2 * 0 + 1];
			const float x21 = m_range[2 * 1 + 0];
			const float x22 = m_range[2 * 1 + 1];
			const float s1 = m_tics_label_size[0];
			const float s2 = m_tics_label_size[1];
			vertices::Text3D* vbo_ptr = vbo_data_text_3D();
			const Font* font_1 = m_scene->font(m_tics_font[0]);
			const Font* font_2 = m_scene->font(m_tics_font[1]);
			//vbo data
			uint32_t vbo_counter = 0;
			for(uint32_t i = 0; i < n1 + 2; i++)
			{
				float sw = 0;
				float w2 = -s1;
				float w1 = float(i) / (n1 + 1);
				const float x1 = x11 + i * (x12 - x11) / (n1 + 1);
				uint32_t nc = sprintf(label, m_tics_format[0], x1);
				for(uint32_t j = 0; j < nc; j++)
				{
					//character
					font_1->character(label[j]).coordinates(tc);
					const int32_t w = font_1->character(label[j]).width();
					const int32_t h = font_1->character(label[j]).height();
					const int32_t r = font_1->character(label[j]).advance();
					const int32_t a = font_1->character(label[j]).bearing(0);
					const int32_t b = font_1->character(label[j]).bearing(1);
					//position
					xc[2 * 3 + 0] = xc[2 * 0 + 0] = w1 + s1 / font_1->height() * a;
					xc[2 * 3 + 1] = xc[2 * 2 + 1] = w2 + s1 / font_1->height() * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = w1 + s1 / font_1->height() * (a + w);
					xc[2 * 1 + 1] = xc[2 * 0 + 1] = w2 + s1 / font_1->height() * (b - h);
					//vertices
					for(uint32_t k = 0; k < 4; k++)
					{
						vbo_ptr[4 * vbo_counter + k].m_color = m_frame_color;
						vbo_ptr[4 * vbo_counter + k].m_texture_coordinates = tc + 2 * k;
						vbo_ptr[4 * vbo_counter + k].m_position = {xc[2 * k + 0], xc[2 * k + 1], 0};
					}
					vbo_counter++;
					w1 += s1 / font_1->height() * r;
					sw += s1 / font_1->height() * r;
				}
				for(uint32_t j = 0; j < nc; j++)
				{
					for(uint32_t k = 0; k < 4; k++)
					{
						vbo_ptr[4 * (vbo_counter - nc + j) + k].m_position[0] -= sw / 2;
					}
				}
			}
			for(uint32_t i = 0; i < n2 + 2; i++)
			{
				float w1 = 0;
				float w2 = float(i) / (n2 + 1) - s2 / 2;
				const float x2 = x21 + i * (x22 - x21) / (n2 + 1);
				uint32_t nc = sprintf(label, m_tics_format[1], x2);
				for(uint32_t j = 0; j < nc; j++)
				{
					//character
					font_2->character(label[j]).coordinates(tc);
					const int32_t w = font_2->character(label[j]).width();
					const int32_t h = font_2->character(label[j]).height();
					const int32_t r = font_2->character(label[j]).advance();
					const int32_t a = font_2->character(label[j]).bearing(0);
					const int32_t b = font_2->character(label[j]).bearing(1);
					//position
					xc[2 * 3 + 0] = xc[2 * 0 + 0] = w1 + s2 / font_2->height() * a;
					xc[2 * 3 + 1] = xc[2 * 2 + 1] = w2 + s2 / font_2->height() * b;
					xc[2 * 1 + 0] = xc[2 * 2 + 0] = w1 + s2 / font_2->height() * (a + w);
					xc[2 * 1 + 1] = xc[2 * 0 + 1] = w2 + s2 / font_2->height() * (b - h);
					//vertices
					for(uint32_t k = 0; k < 4; k++)
					{
						vbo_ptr[4 * vbo_counter + k].m_color = m_frame_color;
						vbo_ptr[4 * vbo_counter + k].m_texture_coordinates = tc + 2 * k;
						vbo_ptr[4 * vbo_counter + k].m_position = {xc[2 * k + 0], xc[2 * k + 1], 0};
					}
					vbo_counter++;
					w1 += s2 / font_2->height() * r;
				}
				for(uint32_t j = 0; j < nc; j++)
				{
					for(uint32_t k = 0; k < 4; k++)
					{
						vbo_ptr[4 * (vbo_counter - nc + j) + k].m_position[0] -= w1;
					}
				}
			}
			//ibo data
			uint32_t ibo_counter = 0;
			for(uint32_t i = 0; i < n1 + 2; i++)
			{
				const float x1 = x11 + i * (x12 - x11) / (n1 + 1);
				uint32_t nc = sprintf(label, m_tics_format[0], x1);
				for(uint32_t j = 0; j < nc; j++)
				{
					ibo_ptr[6 * ibo_counter + 3 * 0 + 0] = m_vbo_index[2] + 4 * ibo_counter + 0;
					ibo_ptr[6 * ibo_counter + 3 * 0 + 1] = m_vbo_index[2] + 4 * ibo_counter + 1;
					ibo_ptr[6 * ibo_counter + 3 * 0 + 2] = m_vbo_index[2] + 4 * ibo_counter + 2;
					ibo_ptr[6 * ibo_counter + 3 * 1 + 0] = m_vbo_index[2] + 4 * ibo_counter + 0;
					ibo_ptr[6 * ibo_counter + 3 * 1 + 1] = m_vbo_index[2] + 4 * ibo_counter + 2;
					ibo_ptr[6 * ibo_counter + 3 * 1 + 2] = m_vbo_index[2] + 4 * ibo_counter + 3;
					ibo_counter++;
				}
			}
			for(uint32_t i = 0; i < n2 + 2; i++)
			{
				const float x2 = x21 + i * (x22 - x21) / (n2 + 1);
				uint32_t nc = sprintf(label, m_tics_format[1], x2);
				for(uint32_t j = 0; j < nc; j++)
				{
					ibo_ptr[6 * ibo_counter + 3 * 0 + 0] = m_vbo_index[2] + 4 * ibo_counter + 0;
					ibo_ptr[6 * ibo_counter + 3 * 0 + 1] = m_vbo_index[2] + 4 * ibo_counter + 1;
					ibo_ptr[6 * ibo_counter + 3 * 0 + 2] = m_vbo_index[2] + 4 * ibo_counter + 2;
					ibo_ptr[6 * ibo_counter + 3 * 1 + 0] = m_vbo_index[2] + 4 * ibo_counter + 0;
					ibo_ptr[6 * ibo_counter + 3 * 1 + 1] = m_vbo_index[2] + 4 * ibo_counter + 2;
					ibo_ptr[6 * ibo_counter + 3 * 1 + 2] = m_vbo_index[2] + 4 * ibo_counter + 3;
					ibo_counter++;
				}
			}
		}
	}
}