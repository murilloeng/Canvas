//std
#include <cmath>

//canvas
#include "Canvas/inc/Palettes/Palette.hpp"

namespace canvas
{
	namespace palettes
	{
		//constructor
		Palette::Palette(void) : m_size(0), m_colors(nullptr)
		{
			type(palettes::type::moreland);
		}

		//destructor
		Palette::~Palette(void)
		{
			return;
		}

		//data
		unsigned Palette::size(void) const
		{
			return m_size;
		}
		palettes::type Palette::type(void) const
		{
			return m_type;
		}
		palettes::type Palette::type(palettes::type type)
		{
			load(type);
			return m_type = type;
		}

		//name
		const char* Palette::name(void) const
		{
			return name(m_type);
		}
		const char* Palette::name(palettes::type type)
		{
			//data
			const char* names[] = {"jet", "greys", "plasma", "whylrd", "viridis", "moreland", "spectral"};
			//name
			for(unsigned i = 0; i < unsigned(palettes::type::last); i++)
			{
				if(type == palettes::type(i))
				{
					return names[i];
				}
			}
			return "error";
		}

		//color
		Color Palette::color(float value, float value_min, float value_max) const
		{
			//data
			Color color;
			value = fminf(fmaxf((value - value_min) / (value_max - value_min), 0.0f), 1.0f);
			//check
			if(value == 0.0f)
			{
				const float* color_ptr = m_colors;
				return Color(color_ptr[0], color_ptr[1], color_ptr[2]);
			}
			if(value == 1.0f)
			{
				const float* color_ptr = m_colors + 3 * (m_size - 1);
				return Color(color_ptr[0], color_ptr[1], color_ptr[2]);
			}
			//index
			value *= m_size - 1;
			const unsigned index = (unsigned) floor(value);
			color[0] = (1 + index - value) * m_colors[3 * index + 0] + (value - index) * m_colors[3 * index + 3];
			color[1] = (1 + index - value) * m_colors[3 * index + 1] + (value - index) * m_colors[3 * index + 4];
			color[2] = (1 + index - value) * m_colors[3 * index + 2] + (value - index) * m_colors[3 * index + 5];
			//return
			return color;
		}

		//load
		void Palette::load(palettes::type type)
		{
			//data
			const float* colors[] = {
				m_palette_jet,
				m_palette_greys,
				m_palette_plasma,
				m_palette_whylrd,
				m_palette_viridis,
				m_palette_moreland,
				m_palette_spectral
			};
			const unsigned sizes[] = {9, 8, 256, 5, 256, 257, 8};
			//load
			for(unsigned i = 0; i < unsigned(palettes::type::last); i++)
			{
				if(type == palettes::type(i))
				{
					m_size = sizes[i];
					m_colors = colors[i];
				}
			}
		}
	}
}