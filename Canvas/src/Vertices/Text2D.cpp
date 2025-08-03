//canvas
#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Text2D::Text2D(void)
		{
			return;
		}

		//destructor
		Text2D::~Text2D(void)
		{
			return;
		}

		//print
		void Text2D::print(void) const
		{
			Vertex2D::print();
			m_color.print("color", true);
			m_texture_coordinates.print("texture", true);
		}
	}
}