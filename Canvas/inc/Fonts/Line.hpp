#pragma once

//std
#include <cstdint>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Item.hpp"

namespace canvas
{
	namespace fonts
	{
		class Line : public Item
		{
		public:
			//constructor
			Line(void);

			//destructor
			~Line(void);

			//print
			void print(void) const override;

			//data
			uint64_t m_points[2][2];
		};
	}
}