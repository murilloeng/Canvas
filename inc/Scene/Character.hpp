#pragma once

//ext
#include "../external/cpp/inc/freetype/freetype.h"

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
		unsigned width(void);
		unsigned height(void);
		unsigned offset(void);
		unsigned advance(void);
		unsigned bearing(unsigned);
		const unsigned char* data(void) const;

		//draw
		void coordinates(float*) const;

		//setup
		void setup(FT_Face, char);

	private:
		//data
		char m_code;
		unsigned m_width;
		unsigned m_height;
		unsigned m_offset;
		unsigned m_advance;
		unsigned char* m_data;
		unsigned m_bearings[2];

		//friends
		friend class Font;
	};
}