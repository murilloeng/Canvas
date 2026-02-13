//canvas
#include "Canvas/Canvas/inc/Vertices/Model2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Model2D::Model2D(void)
		{
			return;
		}

		//destructor
		Model2D::~Model2D(void)
		{
			return;
		}

		//print
		void Model2D::print(void) const
		{
			Vertex2D::print();
			m_color.print("Color", true);
		}
	}
}