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
			int64_t m_points[2][2];
			int64_t m_controls[2][2];
		};
	}
}