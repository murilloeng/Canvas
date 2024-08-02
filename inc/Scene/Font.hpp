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
		static uint32_t width(void);
		static uint32_t height(void);

		std::string name(void) const;
		std::string name(std::string);

		static uint32_t pixels_size(void);
		static uint32_t pixels_size(uint32_t);

		Character& character(uint32_t);
		const Character& character(uint32_t) const;

		//setup
		void setup_texture(void);
		void setup(uint32_t&, uint32_t&);

	protected:
		//data
		bool m_status;
		Scene* m_scene;
		FT_Face m_face;
		std::string m_name;
		Character m_chars[128];
		static uint32_t m_width;
		static uint32_t m_height;
		static uint32_t m_pixels_size;

		//friends
		friend class Scene;
	};
}