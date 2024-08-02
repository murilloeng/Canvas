#pragma once

//ext
#include "external/cpp/inc/freetype/freetype.h"

namespace canvas
{
	class Font;
}

namespace canvas
{
	class Character
	{
	public:
		//constructors
		Character(void);

		//destructor
		~Character(void);

		//data
		uint32_t width(void) const;
		uint32_t height(void) const;
		uint32_t offset(void) const;
		uint32_t advance(void) const;
		uint32_t bearing(uint32_t) const;
		const uint8_t* data(void) const;

		//draw
		void coordinates(float*) const;

		//setup
		void setup(FT_Face, char);

	protected:
		//data
		char m_code;
		uint8_t* m_data;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_offset;
		uint32_t m_advance;
		uint32_t m_bearings[2];

		//friends
		friend class Font;
	};
}