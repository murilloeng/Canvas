//canvas
#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Image3D::Image3D(void)
		{
			return;
		}

		//destructor
		Image3D::~Image3D(void)
		{
			return;
		}

		//print
		void Image3D::print(void) const
		{
			Vertex3D::print();
			m_texture_coordinates.print("texture", true);
		}
	}
}