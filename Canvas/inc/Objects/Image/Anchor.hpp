#pragma once

//std
#include <cstdint>

namespace canvas
{
	class Anchor
	{
	public:
		//constructors
		Anchor(void);
		Anchor(const char*);
		Anchor(uint32_t, uint32_t);

		//destructor
		~Anchor(void);

		//data
		uint32_t vertical(uint32_t);
		uint32_t vertical(void) const;

		uint32_t horizontal(uint32_t);
		uint32_t horizontal(void) const;

		const char* mode(void) const;
		const char* mode(const char*);

	protected:
		//data
		uint32_t m_vertical;
		uint32_t m_horizontal;
	};
}