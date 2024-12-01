//ext
#include "freetype/freetype.h"

//canvas
#include "Canvas/Canvas/inc/Scene/Font.hpp"
#include "Canvas/Canvas/inc/Scene/Character.hpp"

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
		delete[] m_data;
	}

	//data
	uint32_t Character::width(void) const
	{
		return m_width;
	}
	uint32_t Character::height(void) const
	{
		return m_height;
	}
	uint32_t Character::offset(void) const
	{
		return m_offset;
	}
	uint32_t Character::advance(void) const
	{
		return m_advance;
	}
	uint32_t Character::bearing(uint32_t index) const
	{
		return m_bearings[index];
	}
	const uint8_t* Character::data(void) const
	{
		return m_data;
	}

	//draw
	void Character::coordinates(float* coordinates) const
	{
		//data
		const uint32_t w = Font::width();
		const uint32_t h = Font::height();
		//coordinates
		coordinates[2 * 2 + 1] = coordinates[2 * 3 + 1] = 0;
		coordinates[2 * 0 + 0] = coordinates[2 * 3 + 0] = float(m_offset) / w;
		coordinates[2 * 0 + 1] = coordinates[2 * 1 + 1] = float(m_height) / h;
		coordinates[2 * 1 + 0] = coordinates[2 * 2 + 0] = float(m_offset + m_width) / w;
	}

	//setup
	void Character::setup(FT_Face face, char code)
	{
		//setup
		m_code = code;
		m_width = face->glyph->bitmap.width;
		m_height = face->glyph->bitmap.rows;
		m_advance = face->glyph->advance.x / 64;
		m_bearings[1] = face->glyph->bitmap_top;
		m_bearings[0] = face->glyph->bitmap_left;
		//buffer
		if(m_data) delete[] m_data;
		m_data = new uint8_t[m_width * m_height];
		memcpy(m_data, face->glyph->bitmap.buffer, m_width * m_height * sizeof(uint8_t));
	}
}