//canvas
#include "inc/Vertices/Texture.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Texture::Texture(void) : m_color{0, 0, 0}, m_position{0, 0, 0}, m_texture{0, 0}
		{
			return;
		}

		//destructor
		Texture::~Texture(void)
		{
			return;
		}
	}
}