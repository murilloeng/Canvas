#pragma once

//std
#include <cstdint>

namespace canvas
{
	class Color
	{
	public:
		//constructors
		Color(void);
		Color(const char*);
		Color(const float*);
		Color(float, float, float);
		Color(float, float, float, float);

		//destructors
		~Color(void);

		//data
		float channel(uint32_t) const;
		float channel(uint32_t, float);

		const float* channels(void) const;
		const float* channels(const char*);
		const float* channels(const float*);
		const float* channels(float, float, float);
		const float* channels(float, float, float, float);
		
		//linear
		Color inverse(void) const;
		
		//operators
		float& operator[](uint32_t);
		Color& operator=(const float*);
		const float& operator[](uint32_t) const;

		//print
		void print(const char* = "", bool = false) const;

	private:
		//misc
		static void table_conversion(char*, const char*);
		static float string_channel(const char*, uint32_t);

		//data
		float m_channels[4];
	};
}