//std
#include <filesystem>

//OpenGL
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>

//canvas
#include "Canvas/inc/Fonts/Font.hpp"

#include "Canvas/inc/Scene/Scene.hpp"

#include "Canvas/inc/Textures/Texture.hpp"

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
		Font::Font(FT_Library library, const char* name) : m_face{nullptr}, m_name{name}, m_library{library}
		{
			load();
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
			return m_name = name;
		}

		int64_t Font::height(void) const
		{
			return m_face->size->metrics.height >> 6;
		}
		int64_t Font::ascender(void) const
		{
			return m_face->size->metrics.ascender >> 6;
		}
		int64_t Font::descender(void) const
		{
			return m_face->size->metrics.descender >> 6;
		}

		const char* Font::style(void) const
		{
			return m_face->style_name;
		}
		const char* Font::family(void) const
		{
			return m_face->family_name;
		}

		Glyph& Font::glyph(uint32_t index)
		{
			return m_glyphs[index];
		}
		const Glyph& Font::glyph(uint32_t index) const
		{
			return m_glyphs[index];
		}

		const textures::Texture& Font::texture(void) const
		{
			return m_texture;
		}

		void Font::load(void)
		{
			//data
			int64_t w = 0, h = 0;
			const std::string path = fonts_dir + m_name + ".ttf";
			//font
			FT_Done_Face(m_face);
			if(FT_New_Face(m_library, path.c_str(), 0, &m_face))
			{
				throw std::runtime_error("FreeType face loading failed!");
			}
			//size
			if(FT_Set_Pixel_Sizes(m_face, 0, 256))
			{
				throw std::runtime_error("FreeType font size setup failed!");
			}
			//characters
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
			//texture
			m_texture.width(w);
			m_texture.height(h);
			m_texture.format(GL_R8);
			//transfer
			m_texture.allocate();
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			for(const Glyph& glyph : m_glyphs)
			{
				m_texture.transfer(glyph.m_offset, 0, glyph.m_width, glyph.m_height, GL_RED, GL_UNSIGNED_BYTE, glyph.m_data);
			}
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			m_texture.generate_mipmaps();
		}
	}
}