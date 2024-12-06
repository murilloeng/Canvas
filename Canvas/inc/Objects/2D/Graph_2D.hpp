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

			//buffers
			void buffers_data_tics(void) const;
			void buffers_data_frame(void) const;
			void buffers_data_labels(void) const;

			//data
			float m_range[4];
			Color m_frame_color;
			uint32_t m_tics_font[2];
			uint32_t m_tics_count[2];
			char m_tics_format[2][20];
			float m_tics_line_size[2];
			float m_tics_label_size[2];
		};
	}
}