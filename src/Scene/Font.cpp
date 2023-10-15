#pragma once

//std
#include <filesystem>

//ext
#include "../external/cpp/inc/GL/glew.h"

//canvas
#include "inc/Scene/Font.hpp"

namespace canvas
{
	//constructors
	Font::Font(const char* name) : m_status(false), m_name(name)
	{
		return;
	}

	//destructor
	Font::~Font(void)
	{
		FT_Done_Face(m_face);
	}

	//data
	std::string Font::name(void) const
	{
		return m_name;
	}
	std::string Font::name(std::string name)
	{
		m_status = false;
		return m_name = name;
	}

	Character& Font::character(unsigned index)
	{
		return m_chars[index];
	}

	unsigned Font::total_width(void)
	{
		return m_total_width;
	}
	unsigned Font::total_height(void)
	{
		return m_total_height;
	}

	//setup
	void Font::setup_texture(void)
	{
		for(unsigned i = 0; i < 128; i++)
		{
			const unsigned w = m_chars[i].m_width;
			const unsigned h = m_chars[i].m_height;
			const unsigned x = m_chars[i].m_offset;
			const unsigned char* data = m_chars[i].m_data;
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, w, h, GL_RED, GL_UNSIGNED_BYTE, data);
		}
	}
	void Font::setup_ft(void)
	{
		if(FT_Init_FreeType(&m_library))
		{
			fprintf(stderr, "Error: Unable to init FreeType Library!\n");
			exit(EXIT_FAILURE);
		}
	}
	void Font::clean_ft(void)
	{
		FT_Done_FreeType(m_library);
	}
	void Font::setup(unsigned& w, unsigned& h)
	{
		//data
		const std::string path = "C:/Windows/Fonts/" + m_name + ".ttf";
		//font
		if(FT_New_Face(m_library, path.c_str(), 0, &m_face))
		{
			fprintf(stderr, "Error: Failed to load font %s!\n", m_name.c_str());
			exit(EXIT_FAILURE);
		}
		//size
		if(FT_Set_Pixel_Sizes(m_face, 0, 256))
		{
			fprintf(stderr, "Error: Failed to set font %s size!\n", m_name.c_str());
			exit(EXIT_FAILURE);
		}
		//characters
		for(unsigned i = 0; i < 128; i++)
		{
			//load
			if(FT_Load_Char(m_face, i, FT_LOAD_RENDER))
			{
				fprintf(stderr, "Error: Failed to load glyph %d from font %s!\n", i, m_name.c_str());
				exit(EXIT_FAILURE);
			}
			//setup
			m_chars[i].m_offset = w;
			m_chars[i].setup(m_face, i);
			//update
			w += m_chars[i].m_width;
			h = std::max(h, m_chars[i].m_height);
		}
	}

	//static
	FT_Library Font::m_library;
	unsigned Font::m_total_width;
	unsigned Font::m_total_height;
}