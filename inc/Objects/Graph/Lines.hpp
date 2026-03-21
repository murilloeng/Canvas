#pragma once

//std
#include <cstdint>

//Canvas
#include "Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			class Lines
			{
			public:
				//constructor
				Lines(void);

				//destructor
				~Lines(void);

				//data
				Color color(Color);
				Color color(void) const;

				uint32_t width(uint32_t);
				uint32_t width(void) const;

				uint32_t enabled(bool);
				uint32_t enabled(void) const;

				uint32_t dash_size(uint32_t);
				uint32_t dash_size(void) const;

				uint32_t dash_type(uint32_t);
				uint32_t dash_type(void) const;

			private:
				//data
				Color m_color;
				uint32_t m_width;
				uint32_t m_enabled;
				uint32_t m_dash_size;
				uint32_t m_dash_type;
			};
		}
	}
}