//canvas
#include "Canvas/Canvas/inc/Vertices/Vertex2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Vertex2D::Vertex2D(void)
		{
			return;
		}

		//destructor
		Vertex2D::~Vertex2D(void)
		{
			return;
		}

		//print
		void Vertex2D::print(void) const
		{
			m_position.print("Position:", true);
		}
	}
}