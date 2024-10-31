//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/inc/GPU/Texture.hpp"

namespace canvas
{
	//constructor
	Texture::Texture(void)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
	}

	//destructor
	Texture::~Texture(void)
	{
		if(glIsTexture(m_id)) glDeleteTextures(1, &m_id);
	}
}