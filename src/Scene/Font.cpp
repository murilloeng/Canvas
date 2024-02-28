//std
#include <filesystem>

//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/inc/Scene/Font.hpp"
#include "Canvas/inc/Scene/Scene.hpp"

//defines
#ifdef _WIN32
#define fonts_dir "C:/Windows/Fonts/"
#else
#define fonts_dir "/usr/share/fonts/truetype/msttcorefonts/"
#endif

namespace canvas
{
	//constructors
	Font::Font(Scene* scene, const char* name) : m_status(false), m_scene(scene), m_face(nullptr), m_name(name)
	{
		return;
	}

	//destructor
	Font::~Font(void)
	{
		FT_Done_Face(m_face);
	}

	//data
	unsigned Font::width(void)
	{
		return m_width;
	}
	unsigned Font::height(void)
	{
		return m_height;
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

	unsigned Font::pixels_size(void)
	{
		return m_pixels_size;
	}
	unsigned Font::pixels_size(unsigned pixels_size)
	{
		return m_pixels_size = pixels_size;
	}

	Character& Font::character(unsigned index)
	{
		return m_chars[index];
	}
	const Character& Font::character(unsigned index) const
	{
		return m_chars[index];
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
	void Font::setup(unsigned& w, unsigned& h)
	{
		//data
		const std::string path = fonts_dir + m_name + ".ttf";
		//font
		FT_Done_Face(m_face);
		if(FT_New_Face(m_scene->m_ft_library, path.c_str(), 0, &m_face))
		{
			fprintf(stderr, "Error: Failed to load font %s!\n", m_name.c_str());
			exit(EXIT_FAILURE);
		}
		//size
		if(FT_Set_Pixel_Sizes(m_face, 0, m_pixels_size))
		{
			fprintf(stderr, "Error: Failed to set font %s size!\n", m_name.c_str());
			exit(EXIT_FAILURE);
		}
		//characters
		m_status = true;
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
	unsigned Font::m_width;
	unsigned Font::m_height;
	unsigned Font::m_pixels_size = 256;
}