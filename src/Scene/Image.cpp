#pragma once

//def
#define STB_IMAGE_IMPLEMENTATION

//ext
#include "../external/cpp/inc/stb_image.h"

//canvas
#include "inc/Scene/Image.hpp"

namespace canvas
{
	//constructors
	Image::Image(void) : m_data(nullptr)
	{
		return;
	}
	
	//destructor
	Image::~Image(void)
	{
		if(m_data) stbi_image_free(m_data);
	}

	//load
	void Image::load(void)
	{
		//load
		int w, h, c;
		stbi_set_flip_vertically_on_load(true);
		m_data = stbi_load(m_path.c_str(), &w, &h, &c, STBI_rgb_alpha);
		//setup
		m_width = w;
		m_height = h;
	}
}