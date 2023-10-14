#pragma once

//std
#include <string>

//ext
#include "../external/cpp/inc/freetype/freetype.h"

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
		std::string name(void) const;
		std::string name(std::string);

		Character& character(unsigned);

		static unsigned total_width(void);
		static unsigned total_height(void);

		//setup
		void setup(void);
		void load_char(char);
		void setup_texture(void);
		static void setup_ft(void);
		static void clean_ft(void);
		void setup_chars(unsigned&, unsigned&);

	private:
		//data
		bool m_status;
		FT_Face m_face;
		std::string m_name;
		Character m_chars[128];
		static FT_Library m_library;
		static unsigned m_total_width;
		static unsigned m_total_height;

		//friends
		friend class Scene;
	};
}