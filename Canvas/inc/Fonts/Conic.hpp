#pragma once

//std
#include <cstdint>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Item.hpp"

namespace canvas
{
	namespace fonts
	{
		class Conic : public Item
		{
		public:
			//constructor
			Conic(void);

			//destructor
			~Conic(void);

			//print
			void print(void) const override;

			//data
			uint64_t m_control[2];
			uint64_t m_points[2][2];
		};
	}
}