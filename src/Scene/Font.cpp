#pragma once

//ext
#include "../external/cpp/inc/GL/glew.h"

//canvas
#include "inc/Scene/Font.hpp"

namespace canvas
{
	//constructors
	Font::Font(const char* name, unsigned size) : m_status(false), m_name(name), m_size(size)
	{
		//data
		std::string path = "C:/Windows/Fonts/" + m_name + ".ttf";
		//face
		FT_Done_Face(m_face);
		if(FT_New_Face(m_library, path.c_str(), 0, &m_face))
		{
			fprintf(stderr, "Error: Failed to load font!\n");
			exit(EXIT_FAILURE);
		}
		//size
		if(FT_Set_Pixel_Sizes(m_face, 0, m_size))
		{
			fprintf(stderr, "Error: Failed to set font size!\n");
			exit(EXIT_FAILURE);
		}
		//characters
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for(unsigned code = 0; code < 128; code++)
		{
			// m_characters[code].setup(m_face, code);
		}
	}

	//destructor
	Font::~Font(void)
	{
		FT_Done_Face(m_face);
	}

	//data
	unsigned Font::size(void) const
	{
		return m_size;
	}
	unsigned Font::size(unsigned size)
	{
		m_status = false;
		return m_size = size;
	}

	std::string Font::name(void) const
	{
		return m_name;
	}
	std::string Font::name(std::string name)
	{
		m_status = false;
		return m_name = name;
	}

	//setup
	void Font::setup(void)
	{

	}
	void Font::setup_ft(void)
	{
		if(FT_Init_FreeType(&m_library))
		{
			printf("Error: Could not init FreeType Library!\n");
			exit(EXIT_FAILURE);
		}
	}
	void Font::clean_ft(void)
	{
		FT_Done_FreeType(m_library);
	}

	//static
	FT_Library Font::m_library;
}