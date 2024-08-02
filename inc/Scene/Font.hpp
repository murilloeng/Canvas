#pragma once

//std
#include <string>

//ext
#include "external/cpp/inc/freetype/freetype.h"

//canvas
#include "Canvas/inc/Scene/Character.hpp"

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
		Font(Scene*, const char*);

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

	protected:
		//data
		bool m_status;
		Scene* m_scene;
		FT_Face m_face;
		std::string m_name;
		Character m_chars[128];
		static unsigned m_width;
		static unsigned m_height;
		static unsigned m_pixels_size;

		//friends
		friend class Scene;
	};
}