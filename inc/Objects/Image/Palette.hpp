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

			//buffers
			void vbo_size(uint32_t[]) const override;
			void ibo_size(uint32_t[]) const override;

			//draw
			void ibo_fill_data(uint32_t**) const;
			void ibo_text_data(uint32_t**) const;
			void ibo_stroke_data(uint32_t**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_text_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

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