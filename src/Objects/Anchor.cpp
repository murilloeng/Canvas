#pragma once

//std
#include <cstring>

//canvas
#include "inc/Objects/Anchor.hpp"

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
	Anchor::Anchor(unsigned horizontal, unsigned vertical) : m_vertical(vertical), m_horizontal(horizontal)
	{
		return;
	}

	//destructor
	Anchor::~Anchor(void)
	{
		return;
	}

	//data
	unsigned Anchor::vertical(void) const
	{
		return m_vertical;
	}
	unsigned Anchor::vertical(unsigned vertical)
	{
		return m_vertical = vertical;
	}

	unsigned Anchor::horizontal(void) const
	{
		return m_horizontal;
	}
	unsigned Anchor::horizontal(unsigned horizontal)
	{
		return m_horizontal = horizontal;
	}

	const char* Anchor::mode(void) const
	{
		//data
		const unsigned v[] = {0, 0, 0, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2};
		const unsigned h[] = {0, 2, 0, 0, 0, 1, 2, 0, 1, 2, 0, 1, 2};
		const char* modes[] = {"W", "E", "S", "N", "SW", "SC", "SE", "CW", "CC", "CE", "NW", "NC", "NE"};
		//mode
		for(unsigned i = 0; i < sizeof(v) / sizeof(unsigned); i++)
		{
			if(m_vertical == v[i] && m_horizontal == h[i])
			{
				return modes[i];
			}
		}
	}
	const char* Anchor::mode(const char* mode)
	{
		//data
		const unsigned v[] = {0, 0, 0, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2};
		const unsigned h[] = {0, 2, 0, 0, 0, 1, 2, 0, 1, 2, 0, 1, 2};
		const char* modes[] = {"W", "E", "S", "N", "SW", "SC", "SE", "CW", "CC", "CE", "NW", "NC", "NE"};
		//mode
		for(unsigned i = 0; i < sizeof(v) / sizeof(unsigned); i++)
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