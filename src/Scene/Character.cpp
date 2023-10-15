#pragma once

//canvas
#include "inc/Scene/Font.hpp"
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

	//data
	unsigned Character::width(void)
	{
		return m_width;
	}
	unsigned Character::height(void)
	{
		return m_height;
	}
	unsigned Character::offset(void)
	{
		return m_offset;
	}
	unsigned Character::advance(void)
	{
		return m_advance;
	}
	unsigned Character::bearing(unsigned index)
	{
		return m_bearings[index];
	}
	const unsigned char* Character::data(void) const
	{
		return m_data;
	}

	//draw
	void Character::coordinates(float* coordinates) const
	{
		//data
		const unsigned w = Font::total_width();
		const unsigned h = Font::total_height();
		//coordinates
		coordinates[3] = 0;
		coordinates[0] = float(m_offset) / w;
		coordinates[2] = float(m_height) / h;
		coordinates[1] = float(m_offset + m_width) / w;
	}

	//setup
	void Character::setup(FT_Face face, char code)
	{
		m_code = code;
		m_width = face->glyph->bitmap.width;
		m_height = face->glyph->bitmap.rows;
		m_advance = 64 * face->glyph->advance.x;
		m_bearings[1] = face->glyph->bitmap_top;
		m_bearings[0] = face->glyph->bitmap_left;

		if(m_data) delete[] m_data;
		m_data = new unsigned char[m_width * m_height];
		memcpy(m_data, face->glyph->bitmap.buffer, m_width * m_height * sizeof(unsigned char));
	}
}