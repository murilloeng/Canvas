//canvas
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Model3D::Model3D(void)
		{
			return;
		}

		//destructor
		Model3D::~Model3D(void)
		{
			return;
		}

		//print
		void Model3D::print(void) const
		{
			Vertex3D::print();
			m_color.print("Color", true);
		}
	}
}