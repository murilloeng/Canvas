#pragma once

//std
#include <string>

//ext
#include "../external/cpp/inc/freetype/freetype.h"

namespace canvas
{
	class Font
	{
	public:
		//constructors
		Font(const char*, unsigned);

		//destructor
		~Font(void);

		//data
		unsigned size(unsigned);
		unsigned size(void) const;

		std::string name(void) const;
		std::string name(std::string);

		//setup
		void setup(void);
		static void setup_ft(void);
		static void clean_ft(void);

	private:
		//data
		bool m_status;
		FT_Face m_face;
		unsigned m_size;
		std::string m_name;
		static FT_Library m_library;
	};
}