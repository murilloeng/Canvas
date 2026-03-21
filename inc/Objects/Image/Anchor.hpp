#pragma once

//std
#include <cstdint>

namespace canvas
{
	class Anchor
	{
	public:
		//types
		enum class Vertical : uint32_t
		{
			South, Center, North
		};
		enum class Horizontal : uint32_t
		{
			West, Center, East
		};

		//constructors
		Anchor(void);
		Anchor(const char*);
		Anchor(Horizontal, Vertical);

		//destructor
		~Anchor(void);

		//data
		const char* mode(void) const;
		const char* mode(const char*);

		Vertical vertical(Vertical);
		Vertical vertical(void) const;

		Horizontal horizontal(Horizontal);
		Horizontal horizontal(void) const;

	protected:
		//data
		Vertical m_vertical;
		Horizontal m_horizontal;
	};
}