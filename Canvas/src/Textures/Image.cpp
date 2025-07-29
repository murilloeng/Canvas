//std
#include <stdexcept>

//def
#define STB_IMAGE_IMPLEMENTATION

//ext
#include "stb_image.h"

//canvas
#include "Canvas/Canvas/inc/Textures/Image.hpp"

namespace canvas
{
	//constructors
	Image::Image(const char* path) : m_status(false), m_data(nullptr), m_path(path)
	{
		return;
	}

	//destructor
	Image::~Image(void)
	{
		if(m_data) stbi_image_free(m_data);
	}

	//data
	uint32_t Image::width(void) const
	{
		return m_width;
	}
	uint32_t Image::height(void) const
	{
		return m_height;
	}
	std::string Image::path(void) const
	{
		return m_path;
	}
	std::string Image::path(std::string path)
	{
		m_status = false;
		return m_path = path;
	}

	//load
	void Image::load(void)
	{
		//load
		int w, h, c;
		if(m_status) return;
		if(m_data) stbi_image_free(m_data);
		stbi_set_flip_vertically_on_load(true);
		m_data = stbi_load(m_path.c_str(), &w, &h, &c, STBI_rgb_alpha);
		//check
		if(!m_data)
		{
			throw std::runtime_error("STBI image loading of " + m_path + " failed!");
		}
		//setup
		m_width = w;
		m_height = h;
		m_status = true;
	}

	//coordinates
	void Image::coordinates(float* coordinates) const
	{
		coordinates[2] = 0;
		coordinates[0] = float(m_offset) / m_total_width;
		coordinates[3] = float(m_height) / m_total_height;
		coordinates[1] = float(m_offset + m_width) / m_total_width;
	}

	//static
	uint32_t Image::m_total_width = 0;
	uint32_t Image::m_total_height = 0;
}