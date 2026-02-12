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
		};
	}
}