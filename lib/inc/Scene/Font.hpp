#pragma once

//std
#include <string>

//ext
#include "ext/inc/freetype/freetype.h"

//canvas
#include "inc/Scene/Character.hpp"

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
		static void setup_ft(void);
		static void clean_ft(void);
		void setup(unsigned&, unsigned&);

	private:
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