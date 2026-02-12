#pragma once

//std
#include <vector>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Item.hpp"

namespace canvas
{
	namespace fonts
	{
		class Contour
		{
		public:
			//constructor
			Contour(void);

			//destructor
			~Contour(void);

			//print
			void print(void) const;

			//data
			std::vector<Item*> m_items;
		};
	}
}