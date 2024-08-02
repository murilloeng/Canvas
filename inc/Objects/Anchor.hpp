#pragma once

namespace canvas
{
	class Anchor
	{
	public:
		//constructors
		Anchor(void);
		Anchor(const char*);
		Anchor(unsigned, unsigned);

		//destructor
		~Anchor(void);

		//data
		unsigned vertical(unsigned);
		unsigned vertical(void) const;

		unsigned horizontal(unsigned);
		unsigned horizontal(void) const;

		const char* mode(void) const;
		const char* mode(const char*);

	protected:
		//data
		unsigned m_vertical;
		unsigned m_horizontal;
	};
}