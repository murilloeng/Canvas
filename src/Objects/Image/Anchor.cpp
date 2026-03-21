//std
#include <cstring>

//canvas
#include "Canvas/inc/Objects/Image/Anchor.hpp"

namespace canvas
{
	//constructors
	Anchor::Anchor(void) : m_vertical(Vertical::Center), m_horizontal(Horizontal::Center)
	{
		return;
	}
	Anchor::Anchor(const char* mode)
	{
		this->mode(mode);
	}
	Anchor::Anchor(Horizontal horizontal, Vertical vertical) : m_vertical(vertical), m_horizontal(horizontal)
	{
		return;
	}

	//destructor
	Anchor::~Anchor(void)
	{
		return;
	}

	//data
	const char* Anchor::mode(void) const
	{
		//data
		const Vertical vertical[] = {
			Vertical::Center, Vertical::Center, Vertical::South, Vertical::North, 
			Vertical::South, Vertical::South, Vertical::South, 
			Vertical::Center, Vertical::Center, Vertical::Center, 
			Vertical::North, Vertical::North, Vertical::North
		};
		const Horizontal horizontal[] = {
			Horizontal::West, Horizontal::East, Horizontal::Center, Horizontal::Center, 
			Horizontal::West, Horizontal::Center, Horizontal::East, 
			Horizontal::West, Horizontal::Center, Horizontal::East,
			Horizontal::West, Horizontal::Center, Horizontal::East,
		};
		const char* modes[] = {"W", "E", "S", "N", "SW", "SC", "SE", "CW", "CC", "CE", "NW", "NC", "NE"};
		//mode
		for(uint32_t i = 0; i < 13; i++)
		{
			if(m_vertical == vertical[i] && m_horizontal == horizontal[i])
			{
				return modes[i];
			}
		}
		return "Error";
	}
	const char* Anchor::mode(const char* mode)
	{
		//data
		const Vertical vertical[] = {
			Vertical::Center, Vertical::Center, Vertical::South, Vertical::North, 
			Vertical::South, Vertical::South, Vertical::South, 
			Vertical::Center, Vertical::Center, Vertical::Center, 
			Vertical::North, Vertical::North, Vertical::North
		};
		const Horizontal horizontal[] = {
			Horizontal::West, Horizontal::East, Horizontal::Center, Horizontal::Center, 
			Horizontal::West, Horizontal::Center, Horizontal::East, 
			Horizontal::West, Horizontal::Center, Horizontal::East,
			Horizontal::West, Horizontal::Center, Horizontal::East,
		};
		const char* modes[] = {"W", "E", "S", "N", "SW", "SC", "SE", "CW", "CC", "CE", "NW", "NC", "NE"};
		//mode
		for(uint32_t i = 0; i < 13; i++)
		{
			if(strcmp(modes[i], mode) == 0)
			{
				m_vertical = vertical[i];
				m_horizontal = horizontal[i];
			}
		}
		return mode;
	}

	Anchor::Vertical Anchor::vertical(void) const
	{
		return m_vertical;
	}
	Anchor::Vertical Anchor::vertical(Vertical vertical)
	{
		return m_vertical = vertical;
	}

	Anchor::Horizontal Anchor::horizontal(void) const
	{
		return m_horizontal;
	}
	Anchor::Horizontal Anchor::horizontal(Horizontal horizontal)
	{
		return m_horizontal = horizontal;
	}
}