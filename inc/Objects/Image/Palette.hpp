#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Object.hpp"
#include "Canvas/inc/Palettes/Palette.hpp"

namespace canvas
{
	namespace objects
	{
		class Palette : public Object
		{
		public:
			//constructors
			Palette(void);

			//destructor
			~Palette(void);

			//data
			float min(float);
			float min(void) const;

			float max(float);
			float max(void) const;

			float size(float);
			float size(void) const;

			uint32_t font(uint32_t);
			uint32_t font(void) const;

			uint32_t marks(uint32_t);
			uint32_t marks(void) const;

			palettes::Palette& palette(void);

		protected:
			//text
			uint32_t text_width(const char*) const;
			uint32_t text_height(const char*) const;

			//data
			void ibo_fill_data(void) const;
			void vbo_fill_data(void) const;
			void ibo_text_data(void) const;
			void vbo_text_data(void) const;
			void ibo_stroke_data(void) const;
			void vbo_stroke_data(void) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			float m_min;
			float m_max;
			float m_size;
			uint32_t m_font;
			uint32_t m_marks;
			palettes::Palette m_palette;
		};
	}
}