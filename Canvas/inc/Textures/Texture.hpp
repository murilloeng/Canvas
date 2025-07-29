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

		//data
		uint32_t width(uint32_t);
		uint32_t width(void) const;

		uint32_t height(uint32_t);
		uint32_t height(void) const;

		uint32_t format(uint32_t);
		uint32_t format(void) const;

		//GPU
		void bind(void) const;
		void allocate(void) const;
		void transfer(uint32_t, uint32_t, uint32_t, uint32_t, const void*);

	private:
		//data
		uint32_t m_id;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_format;
	};
}