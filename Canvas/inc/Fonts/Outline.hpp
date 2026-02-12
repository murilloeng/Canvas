#pragma once

//std
#include <vector>

//FreeType
#include <freetype2/freetype/freetype.h>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Contour.hpp"
#include "Canvas/Canvas/inc/Fonts/BoundingBox.hpp"

namespace canvas
{
	namespace fonts
	{
		class Outline
		{
		public:
			//constructor
			Outline(void);

			//destructor
			~Outline(void);

			//setup
			void setup(FT_Face);

			//print
			void print(void) const;

			//data
			BoundingBox m_bounding_box;
			std::vector<Contour*> m_contours;
		};
	}
}