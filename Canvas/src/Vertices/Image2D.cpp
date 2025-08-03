//canvas
#include "Canvas/Canvas/inc/Vertices/Image2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Image2D::Image2D(void)
		{
			return;
		}

		//destructor
		Image2D::~Image2D(void)
		{
			return;
		}

		//print
		void Image2D::print(void) const
		{
			Vertex2D::print();
			m_texture_coordinates.print("texture", true);
		}
	}
}