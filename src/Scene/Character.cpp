#pragma once

//canvas
#include "inc/Scene/Character.hpp"

//ext
#include "../external/cpp/inc/freetype/freetype.h"

namespace canvas
{
	//constructores
	Character::Character(void) : m_data(nullptr)
	{
		return;
	}

	//destructor
	Character::~Character(void)
	{
		return;
	}

	//setup
	void Character::setup(FT_Face face, char code)
	{
		m_code = code;
		m_advance = face->glyph->advance.x;
		m_data = face->glyph->bitmap.buffer;
		m_width = face->glyph->bitmap.width;
		m_height = face->glyph->bitmap.rows;
		m_offset[1] = face->glyph->bitmap_top;
		m_offset[0] = face->glyph->bitmap_left;
	}
}