#pragma once

//std
#include <cstdint>

namespace canvas
{
	class Texture
	{
	public:
		//constructor
		Texture(void);

		//destructor
		~Texture(void);

	private:
		//data
		uint32_t m_id;
	};
}