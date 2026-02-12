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

			//type
			Type type(void) const override;

			//print
			void print(void) const override;

			//object
			objects::Object* object(void) const override;

			//intersection
			uint32_t hit(const float*) const override;
			float point(uint32_t, float) const override;

			//data
			int64_t m_control[2];
			int64_t m_points[2][2];
		};
	}
}