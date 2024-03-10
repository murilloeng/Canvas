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

			unsigned font(unsigned);
			unsigned font(void) const;

			unsigned marks(unsigned);
			unsigned marks(void) const;

			palettes::Palette& palette(void);

		protected:
			//text
			unsigned text_width(const char*) const;
			unsigned text_height(const char*) const;

			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_text_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_text_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			float m_min;
			float m_max;
			float m_size;
			unsigned m_font;
			unsigned m_marks;
			palettes::Palette m_palette;
		};
	}
}