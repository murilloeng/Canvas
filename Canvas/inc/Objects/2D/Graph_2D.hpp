#pragma once

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Graph_2D :public Object
		{
		public:
			//constructor
			Graph_2D(void);

			//destructor
			~Graph_2D(void);

			//data
			float range(uint32_t, uint32_t) const;
			float range(uint32_t, uint32_t, float);

			bool labels_latex(uint32_t) const;
			bool labels_latex(uint32_t, bool);
			
			float labels_size(uint32_t) const;
			float labels_size(uint32_t, float);

			uint32_t labels_index(uint32_t) const;
			uint32_t labels_index(uint32_t, uint32_t);

			const char* labels_string(uint32_t) const;
			const char* labels_string(uint32_t, const char*);

			float tics_line_size(uint32_t) const;
			float tics_line_size(uint32_t, float);

			float tics_label_size(uint32_t) const;
			float tics_label_size(uint32_t, float);

			uint32_t tics_font(uint32_t) const;
			uint32_t tics_font(uint32_t, uint32_t);

			uint32_t tics_count(uint32_t) const;
			uint32_t tics_count(uint32_t, uint32_t);

			const char* tics_format(uint32_t) const;
			const char* tics_format(uint32_t, const char*);

		private:
			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//vbo data
			void vbo_data_frame(void) const;
			void vbo_data_tics_lines(void) const;
			void vbo_data_update_text(void) const;
			void vbo_data_update_latex(void) const;
			void vbo_data_label_text_1(void) const;
			void vbo_data_label_text_2(void) const;
			void vbo_data_label_latex_1(void) const;
			void vbo_data_label_latex_2(void) const;
			void vbo_data_tics_labels_1(void) const;
			void vbo_data_tics_labels_2(void) const;

			//ibo data
			void ibo_data_frame(void) const;
			void ibo_data_tics_lines(void) const;
			void ibo_data_label_text_1(void) const;
			void ibo_data_label_text_2(void) const;
			void ibo_data_label_latex_1(void) const;
			void ibo_data_label_latex_2(void) const;
			void ibo_data_tics_labels_1(void) const;
			void ibo_data_tics_labels_2(void) const;

			//data
			float m_range[4];
			Color m_frame_color;
			
			bool m_labels_latex[2];
			float m_labels_size[2];
			uint32_t m_labels_font[2];
			uint32_t m_labels_index[2];
			char m_labels_string[2][200];
			
			uint32_t m_tics_font[2];
			uint32_t m_tics_count[2];
			uint32_t m_tics_chars[2];
			char m_tics_format[2][20];
			float m_tics_line_size[2];
			float m_tics_label_size[2];
		};
	}
}