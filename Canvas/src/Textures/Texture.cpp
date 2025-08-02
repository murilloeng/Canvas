//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Textures/Texture.hpp"

namespace canvas
{
	namespace textures
	{
		//constructor
		Texture::Texture(void) : m_width(0), m_height(0), m_format(0)
		{
			//create
			glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
			//check
			if(!glIsTexture(m_id))
			{
				throw std::runtime_error("OpenGL texture creation failed!");
			}
			//setup
			// glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			// glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			// glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glBindTexture(GL_TEXTURE_2D, m_id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}

		//destructor
		Texture::~Texture(void)
		{
			if(glIsTexture(m_id)) glDeleteTextures(1, &m_id);
		}

		//data
		uint32_t Texture::width(void) const
		{
			return m_width;
		}
		uint32_t Texture::width(uint32_t width)
		{
			return m_width = width;
		}

		uint32_t Texture::height(void) const
		{
			return m_height;
		}
		uint32_t Texture::height(uint32_t height)
		{
			return m_height = height;
		}

		uint32_t Texture::format(void) const
		{
			return m_format;
		}
		uint32_t Texture::format(uint32_t format)
		{
			return m_format = format;
		}

		//bind
		void Texture::bind(void) const
		{
			glBindTexture(GL_TEXTURE_2D, m_id);
		}
		void Texture::bind_unit(GLuint unit) const
		{
			glBindTextureUnit(unit, m_id);
		}

		//data
		void Texture::allocate(void) const
		{
			//storage
			if(m_format == GL_RED) glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			if(m_format == GL_RGBA) glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			//texture
			glBindTexture(GL_TEXTURE_2D, m_id);
			glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, nullptr);
		}
		void Texture::transfer(uint32_t x1, uint32_t x2, uint32_t w, uint32_t h, const void* data)
		{
			glTextureSubImage2D(m_id, 0, x1, x2, w, h, m_format, GL_UNSIGNED_BYTE, data);
		}
	}
}