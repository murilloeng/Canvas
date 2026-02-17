#pragma once

//std
#include <string>
#include <cstdint>

//FreeType
#include <freetype2/freetype/freetype.h>

//canvas
#include "Canvas/Canvas/inc/Fonts/Glyph.hpp"
#include "Canvas/Canvas/inc/Textures/Texture.hpp"

namespace canvas
{
	class Scene;
}

namespace canvas
{
	namespace fonts
	{
		class Font
		{
		public:
			//constructors
			Font(Scene*, const char*);

			//destructor
			~Font(void);

			//data
			std::string name(void) const;
			std::string name(std::string);

			int64_t height(void) const;
			int64_t ascender(void) const;
			int64_t descender(void) const;

			const char* style(void) const;
			const char* family(void) const;

			Glyph& glyph(uint32_t);
			const Glyph& glyph(uint32_t) const;

			const textures::Texture& texture(void) const;

		protected:
			//load
			void load(void);

			//data
			Scene* m_scene;
			FT_Face m_face;
			std::string m_name;
			Glyph m_glyphs[128];
			textures::Texture m_texture;

			//friends
			friend class canvas::Scene;
		};
	}
}