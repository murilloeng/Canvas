//canvas
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Text3D::Text3D(void)
		{
			return;
		}

		//destructor
		Text3D::~Text3D(void)
		{
			return;
		}

		//print
		void Text3D::print(void) const
		{
			Vertex3D::print();
			m_color.print("color", true);
			m_texture_coordinates.print("texture", true);
		}
	}
}