#pragma once

//std
#include <string>

//canvas
#include "inc/Scene/Character.hpp"

namespace canvas
{
	class Scene;
}
class FT_FaceRec_;
class FT_LibraryRec_;

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
		void load_char(char);
		static void setup_ft(void);
		static void clean_ft(void);

	private:
		//data
		bool m_status;
		unsigned m_size;
		std::string m_name;
		FT_FaceRec_* m_face;
		Character m_chars[128];
		static FT_LibraryRec_* m_library;

		//friends
		friend class Scene;
	};
}