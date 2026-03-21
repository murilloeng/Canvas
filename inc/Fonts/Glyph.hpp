#pragma once

//std
#include <cstdint>

//FreeType
#include <freetype2/freetype/freetype.h>

//Canvas
#include "Canvas/inc/Fonts/Outline.hpp"

namespace canvas
{
	namespace fonts
	{
		class Font;
	}
}

namespace canvas
{
	namespace fonts
	{
		class Glyph
		{
		public:
			//constructors
			Glyph(void);

			//destructor
			~Glyph(void);

			//data
			int64_t width(void) const;
			int64_t height(void) const;
			int64_t offset(void) const;
			int64_t advance(void) const;
			int64_t bearing(uint32_t) const;

			const uint8_t* data(void) const;
			const Outline& outline(void) const;

			//setup
			void setup(FT_Face, char);

			//draw
			void coordinates(const Font*, float*) const;

		protected:
			//data
			char m_code;
			uint8_t* m_data;
			int64_t m_width;
			int64_t m_height;
			int64_t m_offset;
			int64_t m_advance;
			int64_t m_bearings[2];

			Outline m_outline;

			//friends
			friend class fonts::Font;
		};
	}
}