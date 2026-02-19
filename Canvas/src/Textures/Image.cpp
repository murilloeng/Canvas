//std
#include <stdexcept>

//def
#define STB_IMAGE_IMPLEMENTATION

//stb
#include <stb/stb_image.h>

//canvas
#include "Canvas/Canvas/inc/Textures/Image.hpp"

namespace canvas
{
	namespace textures
	{
		//constructors
		Image::Image(void)
		{
			return;
		}

		//destructor
		Image::~Image(void)
		{
			return;
		}

		//data
		std::string Image::path(void) const
		{
			return m_path;
		}
		std::string Image::path(std::string path)
		{
			return m_path = path;
		}

		const Texture& Image::texture(void) const
		{
			return m_texture;
		}

		//load
		void Image::load(void)
		{
			//load
			uint8_t* data;
			int32_t w, h, c;
			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(m_path.c_str(), &w, &h, &c, STBI_rgb_alpha);
			//check
			if(!data)
			{
				throw std::runtime_error("STBI image loading of " + m_path + " failed!");
			}
			//texture
			m_texture.width(w);
			m_texture.height(h);
			m_texture.format(GL_RGBA8);
			//transfer
			m_texture.allocate();
			m_texture.transfer(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
			m_texture.generate_mipmaps();
			//deallocate
			stbi_image_free(data);
		}
	}
}