#pragma once

//std
#include <string>
#include <cstdint>

//ext
#include "external/cpp/inc/freetype/freetype.h"

//canvas
#include "Canvas/Canvas/inc/Fonts/Glyph.hpp"

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
			static uint32_t width(void);
			static uint32_t height(void);

			std::string name(void) const;
			std::string name(std::string);

			static uint32_t pixels_size(void);
			static uint32_t pixels_size(uint32_t);

			Glyph& glyph(uint32_t);
			const Glyph& glyph(uint32_t) const;

			//setup
			void cleanup(void);
			void setup_texture(void);
			void setup(uint32_t&, uint32_t&);

		protected:
			//data
			bool m_status;
			Scene* m_scene;
			FT_Face m_face;
			std::string m_name;
			Glyph m_glyphs[128];
			static uint32_t m_width;
			static uint32_t m_height;
			static uint32_t m_pixels_size;

			//friends
			friend class Scene;
		};
	}
}