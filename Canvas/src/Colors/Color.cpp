//std
#include <cstring>
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"

//static
static const char* colors_table[] = {
	"red",			"#ff0000",
	"blue",			"#0000ff",
	"cyan",			"#00ffff",
	"gray",			"#808080",
	"pink",			"#FFC0CB",
	"black",		"#000000",
	"brown",		"#A52A2A",
	"white",		"#ffffff",
	"green",		"#00ff00",
	"purple",		"#800080",
	"orange",		"#FFA500",
	"silver",		"#c0c0c0",
	"violet",		"#EE82EE",
	"yellow",		"#ffff00",
	"magenta",		"#ff00ff",
	"dark green",	"#013220"
};

namespace canvas
{
	//constructors
	Color::Color(void) : m_channels{1.0f, 1.0f, 1.0f, 1.0f}
	{
		return;
	}
	Color::Color(const char* string)
	{
		channels(string);
	}
	Color::Color(const float* channels)
	{
		memcpy(m_channels, channels, 4 * sizeof(float));
	}
	Color::Color(float r, float g, float b) : m_channels{r, g, b, 1.0f}
	{
		return;
	}
	Color::Color(float r, float g, float b, float a) : m_channels{r, g, b, a}
	{
		return;
	}

	//destructor
	Color::~Color(void)
	{
		return;
	}

	//data
	float Color::channel(uint32_t index) const
	{
		return m_channels[index];
	}
	float Color::channel(uint32_t index, float channel)
	{
		return m_channels[index] = channel;
	}

	const float* Color::channels(void) const
	{
		return m_channels;
	}
	const float* Color::channels(const char* string)
	{
		//data
		char color_string[100];
		//convert
		if(string[0] == '#')
		{
			strcpy(color_string, string);
		}
		else
		{
			table_conversion(color_string, string);
		}
		//check
		if(strlen(color_string) < 7 || strlen(color_string) > 9)
		{
			throw std::runtime_error("Error: Invalid color's string!");
		}
		//channels
		m_channels[0] = string_channel(color_string, 0);
		m_channels[1] = string_channel(color_string, 1);
		m_channels[2] = string_channel(color_string, 2);
		m_channels[3] = strlen(color_string) != 9 ? 1.0f : string_channel(color_string, 3);
		//return
		return m_channels;
	}
	const float* Color::channels(const float* channels)
	{
		return (const float*) memcpy(m_channels, channels, 4 * sizeof(float));
	}
	const float* Color::channels(float r, float g, float b)
	{
		return channels(r, g, b, 1.0f);
	}
	const float* Color::channels(float r, float g, float b, float a)
	{
		m_channels[0] = r;
		m_channels[1] = g;
		m_channels[2] = b;
		m_channels[3] = a;
		return m_channels;
	}

	//linear
	Color Color::inverse(void) const
	{
		Color inverse;
		inverse.m_channels[3] = m_channels[3];
		inverse.m_channels[0] = 1 - m_channels[0];
		inverse.m_channels[1] = 1 - m_channels[1];
		inverse.m_channels[2] = 1 - m_channels[2];
		return inverse;
	}
	Color Color::interpolate(const Color& c, float s) const
	{
		return {
			(1 - s) * m_channels[0] + s * c.m_channels[0],
			(1 - s) * m_channels[1] + s * c.m_channels[1],
			(1 - s) * m_channels[2] + s * c.m_channels[2],
			(1 - s) * m_channels[3] + s * c.m_channels[3]
		};
	}

	//operators
	float& Color::operator[](uint32_t index)
	{
		return m_channels[index];
	}
	Color& Color::operator=(const float* channels)
	{
		for(uint32_t i = 0; i < 4; i++)
		{
			m_channels[i] = channels[i];
		}
		return *this;
	}
	const float& Color::operator[](uint32_t index) const
	{
		return m_channels[index];
	}

	//print
	void Color::print(const char* label, bool transpose) const
	{
		//data
		const char* format = transpose ? "%+.2e " : "%+.2e\n";
		//print
		if(strlen(label) != 0)
		{
			printf("%s\n", label);
		}
		for(uint32_t i = 0; i < 4; i++)
		{
			printf(format, m_channels[i]);
		}
		if(transpose) printf("\n");
	}

	//misc
	void Color::table_conversion(char* color_string, const char* string)
	{
		bool test = false;
		for(uint32_t i = 0; i < sizeof(colors_table) / sizeof(char*); i++)
		{
			if(strcmp(string, colors_table[2 * i]) == 0)
			{
				test = true;
				strcpy(color_string, colors_table[2 * i + 1]);
				break;
			}
		}
		if(!test)
		{
			throw std::runtime_error("Error: Invalid color's string!");
		}
	}
	float Color::string_channel(const char* color_string, uint32_t index)
	{
		char channel_string[2];
		memcpy(channel_string, color_string + 2 * index + 1, 2 * sizeof(char));
		return (float) strtol(channel_string, nullptr, 16) / 255;
	}
}