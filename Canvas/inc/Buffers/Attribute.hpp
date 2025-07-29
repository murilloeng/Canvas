#pragma once

//std
#include <cstdint>

namespace canvas
{
	struct Attribute
	{
		//constructor
		Attribute(uint32_t, uint32_t);

		//destructor
		~Attribute(void);

		//size
		uint32_t bitsize(void) const;

		//data
		uint32_t m_type;
		uint32_t m_size;
	};
}