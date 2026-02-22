#pragma once

//std
#include <cstdint>

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			class Axis
			{
			public:
				//constructor
				Axis(void);

				//destructor
				~Axis(void);

				//data
				float font_size(uint32_t);
				float font_size(void) const;

				float ticks_size(float);
				float ticks_size(void) const;

				float range(uint32_t) const;
				float range(uint32_t, float);

				uint32_t ticks_count(uint32_t);
				uint32_t ticks_count(void) const;

			private:
				//data
				float m_range[2];
				float m_font_size;
				float m_ticks_size;
				uint32_t m_ticks_count;
			};
		}
	}
}