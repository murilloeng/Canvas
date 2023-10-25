#pragma once

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
		float channel(unsigned) const;
		float channel(unsigned, float);

		const float* channels(void) const;
		const float* channels(const char*);
		const float* channels(const float*);
		const float* channels(float, float, float);
		const float* channels(float, float, float, float);

		//operators
		float& operator[](unsigned);
		const float& operator[](unsigned) const;

	private:
		//misc
		static void table_conversion(char*, const char*);
		static float string_channel(const char*, unsigned);

		//data
		float m_channels[4];
	};
}