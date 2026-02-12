#pragma once

//std
#include <cstdint>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Item.hpp"

namespace canvas
{
	namespace fonts
	{
		class Cubic : public Item
		{
		public:
			//constructor
			Cubic(void);

			//destructor
			~Cubic(void);

			//print
			void print(void) const override;

			//data
			uint64_t m_points[2][2];
			uint64_t m_controls[2][2];
		};
	}
}