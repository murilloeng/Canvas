//canvas
#include "Canvas/Canvas/inc/Vertices/Vertex3D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Vertex3D::Vertex3D(void)
		{
			return;
		}

		//destructor
		Vertex3D::~Vertex3D(void)
		{
			return;
		}

		//print
		void Vertex3D::print(void) const
		{
			m_position.print("Position", true);
		}
	}
}