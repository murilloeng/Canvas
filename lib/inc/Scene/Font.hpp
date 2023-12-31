#pragma once

//std
#include <string>

//ext
#include "Canvas/ext/inc/freetype/freetype.h"

//canvas
#include "Canvas/lib/inc/Scene/Character.hpp"

namespace canvas
{
	class Scene;
}

namespace canvas
{
	class Font
	{
	public:
		//constructors
		Font(const char*);

		//destructor
		~Font(void);

		//data
		static unsigned width(void);
		static unsigned height(void);

		std::string name(void) const;
		std::string name(std::string);

		static unsigned pixels_size(void);
		static unsigned pixels_size(unsigned);

		Character& character(unsigned);
		const Character& character(unsigned) const;

		//setup
		void setup_texture(void);
		void setup(unsigned&, unsigned&);
		static void setup_freetype(void);
		static void clean_freetype(void);

	protected:
		//data
		bool m_status;
		FT_Face m_face;
		std::string m_name;
		Character m_chars[128];
		static unsigned m_width;
		static unsigned m_height;
		static FT_Library m_library;
		static unsigned m_pixels_size;

		//friends
		friend class Scene;
	};
}