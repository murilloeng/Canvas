//std
#include <filesystem>

//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/Fonts/Font.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Textures/Texture.hpp"

//defines
#ifdef _WIN32
#define fonts_dir "C:/Windows/Fonts/"
#else
#define fonts_dir "/usr/share/fonts/truetype/msttcorefonts/"
#endif

namespace canvas
{
	namespace fonts
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
		uint32_t Font::width(void)
		{
			return m_width;
		}
		uint32_t Font::height(void)
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

		uint32_t Font::pixels_size(void)
		{
			return m_pixels_size;
		}
		uint32_t Font::pixels_size(uint32_t pixels_size)
		{
			return m_pixels_size = pixels_size;
		}

		Glyph& Font::glyph(uint32_t index)
		{
			return m_glyphs[index];
		}
		const Glyph& Font::glyph(uint32_t index) const
		{
			return m_glyphs[index];
		}

		//setup
		void Font::setup_texture(void)
		{
			for(uint32_t i = 0; i < 128; i++)
			{
				const uint32_t w = m_glyphs[i].m_width;
				const uint32_t h = m_glyphs[i].m_height;
				const uint32_t x = m_glyphs[i].m_offset;
				const uint8_t* data = m_glyphs[i].m_data;
				m_scene->m_textures[1]->transfer(x, 0, w, h, data);
			}
		}
		void Font::setup(uint32_t& w, uint32_t& h)
		{
			//data
			const std::string path = fonts_dir + m_name + ".ttf";
			//font
			FT_Done_Face(m_face);
			if(FT_New_Face(m_scene->m_ft_library, path.c_str(), 0, &m_face))
			{
				throw std::runtime_error("FreeType face loading failed!");
			}
			//size
			if(FT_Set_Pixel_Sizes(m_face, 0, m_pixels_size))
			{
				throw std::runtime_error("FreeType font size setup failed!");
			}
			//characters
			m_status = true;
			for(uint32_t i = 0; i < 128; i++)
			{
				//load
				if(FT_Load_Char(m_face, i, FT_LOAD_RENDER))
				{
					throw std::runtime_error("FreeType glyph loading failed!");
				}
				//setup
				m_glyphs[i].m_offset = w;
				m_glyphs[i].setup(m_face, i);
				//update
				w += m_glyphs[i].m_width;
				h = std::max(h, m_glyphs[i].m_height);
			}
		}

		//static
		uint32_t Font::m_width;
		uint32_t Font::m_height;
		uint32_t Font::m_pixels_size = 256;
	}
}