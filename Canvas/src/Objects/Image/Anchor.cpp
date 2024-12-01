//std
#include <cstring>

//canvas
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"

namespace canvas
{
	//constructors
	Anchor::Anchor(void) : m_vertical(0), m_horizontal(0)
	{
		return;
	}
	Anchor::Anchor(const char* mode)
	{
		this->mode(mode);
	}
	Anchor::Anchor(uint32_t horizontal, uint32_t vertical) : m_vertical(vertical), m_horizontal(horizontal)
	{
		return;
	}

	//destructor
	Anchor::~Anchor(void)
	{
		return;
	}

	//data
	uint32_t Anchor::vertical(void) const
	{
		return m_vertical;
	}
	uint32_t Anchor::vertical(uint32_t vertical)
	{
		return m_vertical = vertical;
	}

	uint32_t Anchor::horizontal(void) const
	{
		return m_horizontal;
	}
	uint32_t Anchor::horizontal(uint32_t horizontal)
	{
		return m_horizontal = horizontal;
	}

	const char* Anchor::mode(void) const
	{
		//data
		const uint32_t v[] = {0, 0, 0, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2};
		const uint32_t h[] = {0, 2, 0, 0, 0, 1, 2, 0, 1, 2, 0, 1, 2};
		const char* modes[] = {"W", "E", "S", "N", "SW", "SC", "SE", "CW", "CC", "CE", "NW", "NC", "NE"};
		//mode
		for(uint32_t i = 0; i < sizeof(v) / sizeof(uint32_t); i++)
		{
			if(m_vertical == v[i] && m_horizontal == h[i])
			{
				return modes[i];
			}
		}
		return "Error";
	}
	const char* Anchor::mode(const char* mode)
	{
		//data
		const uint32_t v[] = {0, 0, 0, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2};
		const uint32_t h[] = {0, 2, 0, 0, 0, 1, 2, 0, 1, 2, 0, 1, 2};
		const char* modes[] = {"W", "E", "S", "N", "SW", "SC", "SE", "CW", "CC", "CE", "NW", "NC", "NE"};
		//mode
		for(uint32_t i = 0; i < sizeof(v) / sizeof(uint32_t); i++)
		{
			if(strcmp(modes[i], mode) == 0)
			{
				m_vertical = v[i];
				m_horizontal = h[i];
			}
		}
		return mode;
	}
}