//canvas
#include "inc/Vertices/Text.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Text::Text(void) : m_color{0, 0, 0}, m_texture{0, 0}, m_position{0, 0, 0}
		{
			return;
		}

		//destructor
		Text::~Text(void)
		{
			return;
		}
	}
}