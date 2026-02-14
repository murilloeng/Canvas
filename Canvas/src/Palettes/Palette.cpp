//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Palettes/Palette.hpp"

namespace canvas
{
	namespace palettes
	{
		//constructor
		Palette::Palette(void) : m_size(0), m_colors(nullptr)
		{
			type(Type::Spectral);
		}
		Palette::Palette(Type type) : m_size(0), m_colors(nullptr)
		{
			this->type(type);
		}

		//destructor
		Palette::~Palette(void)
		{
			return;
		}

		//data
		uint32_t Palette::size(void) const
		{
			return m_size;
		}
		Palette::Type Palette::type(Type type)
		{
			load(type);
			return m_type = type;
		}
		Palette::Type Palette::type(void) const
		{
			return m_type;
		}

		//name
		const char* Palette::name(void) const
		{
			return name(m_type);
		}
		const char* Palette::name(Type type)
		{
			//data
			const char* names[] = {"Jet", "Greys", "Plasma", "Whylrd", "Viridis", "Moreland", "Spectral"};
			//name
			for(uint32_t i = 0; i < uint32_t(Type::last); i++)
			{
				if(type == Type(i))
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
			const uint32_t index = (uint32_t) floor(value);
			color[0] = (1 + index - value) * m_colors[3 * index + 0] + (value - index) * m_colors[3 * index + 3];
			color[1] = (1 + index - value) * m_colors[3 * index + 1] + (value - index) * m_colors[3 * index + 4];
			color[2] = (1 + index - value) * m_colors[3 * index + 2] + (value - index) * m_colors[3 * index + 5];
			//return
			return color;
		}

		//load
		void Palette::load(Type type)
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
			const uint32_t sizes[] = {9, 8, 256, 5, 256, 257, 8};
			//load
			for(uint32_t i = 0; i < uint32_t(Type::last); i++)
			{
				if(type == Type(i))
				{
					m_size = sizes[i];
					m_colors = colors[i];
				}
			}
		}
	}
}