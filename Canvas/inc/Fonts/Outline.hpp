#pragma once

//std
#include <vector>

//FreeType
#include <freetype2/freetype/freetype.h>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Contour.hpp"

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
			std::vector<Contour*> m_contours;
		};
	}
}