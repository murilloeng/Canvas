#pragma once

//std
#include <cstdint>

//FreeType
#include <freetype2/freetype/ftoutln.h>

namespace canvas
{
	namespace fonts
	{
		class BoundingBox
		{
		public:
			//constructor
			BoundingBox(void);
			BoundingBox(const FT_BBox&);

			//destructor
			~BoundingBox(void);

			//print
			void print(void) const;

			//data
			int64_t m_min[2];
			int64_t m_max[2];
		};
	}
}