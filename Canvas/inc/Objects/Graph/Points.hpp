#pragma once

//std
#include <cstdint>

//Canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			class Points
			{
			public:
				//constructor
				Points(void);

				//destructor
				~Points(void);

				//data
				Color color(Color);
				Color color(void) const;

				uint32_t size(uint32_t);
				uint32_t size(void) const;

				uint32_t skip(uint32_t);
				uint32_t skip(void) const;

				uint32_t type(uint32_t);
				uint32_t type(void) const;

				uint32_t enabled(bool);
				uint32_t enabled(void) const;

			private:
				//data
				Color m_color;
				uint32_t m_size;
				uint32_t m_skip;
				uint32_t m_type;
				uint32_t m_enabled;
			};
		}
	}
}