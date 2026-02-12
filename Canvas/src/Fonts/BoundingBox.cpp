//Canvas
#include "Canvas/Canvas/inc/Fonts/BoundingBox.hpp"

namespace canvas
{
	namespace fonts
	{
		//constructor
		BoundingBox::BoundingBox(void) : m_min{-INT64_MAX, -INT64_MAX}, m_max{INT64_MAX, INT64_MAX}
		{
			return;
		}
		BoundingBox::BoundingBox(const FT_BBox& box) : m_min{box.xMin, box.yMin}, m_max{box.xMax, box.yMax}
		{
			return;
		}
		
		//destructor
		BoundingBox::~BoundingBox(void)
		{
			return;
		}

		//print
		void BoundingBox::print(void) const
		{
			printf("Bounding box:\n");
			printf("\tMin: %zd %zd\n", m_min[0], m_min[1]);
			printf("\tMax: %zd %zd\n", m_max[0], m_max[1]);
		}
	}
}