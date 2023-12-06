//std
#include <cstdio>
#include <cstdlib>
#include <cstring>

//canvas
#include "inc/Colors/Color.hpp"

//static
static const char* colors_table[] = {
	"red",		"#ff0000",
	"blue",		"#0000ff",
	"cyan",		"#00ffff",
	"gray",		"#808080",
	"pink",		"#FFC0CB",
	"black",	"#000000",
	"brown",	"#A52A2A",
	"white",	"#ffffff",
	"green",	"#00ff00",
	"purple",	"#800080",
	"orange",	"#FFA500",
	"silver",	"#c0c0c0",
	"violet",	"#EE82EE",
	"yellow",	"#ffff00",
	"magenta",	"#ff00ff"
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
	float Color::channel(unsigned index) const
	{
		return m_channels[index];
	}
	float Color::channel(unsigned index, float channel)
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
			fprintf(stderr, "Error: Invalid color's string!\n");
			exit(EXIT_FAILURE);
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

	//operators
	float& Color::operator[](unsigned index)
	{
		return m_channels[index];
	}
	Color& Color::operator=(const float* channels)
	{
		for(unsigned i = 0; i < 4; i++)
		{
			m_channels[i] = channels[i];
		}
		return *this;
	}
	const float& Color::operator[](unsigned index) const
	{
		return m_channels[index];
	}

	//misc
	void Color::table_conversion(char* color_string, const char* string)
	{
		bool test = false;
		for(unsigned i = 0; i < sizeof(colors_table) / sizeof(char*); i++)
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
			fprintf(stderr, "Error: Invalid color's string!\n");
			exit(EXIT_FAILURE);
		}
	}
	float Color::string_channel(const char* color_string, unsigned index)
	{
		char channel_string[2];
		memcpy(channel_string, color_string + 2 * index + 1, 2 * sizeof(char));
		return (float) strtol(channel_string, nullptr, 16) / 255;
	}
}