#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Palettes/Types.hpp"

namespace canvas
{
	namespace palettes
	{
		class Palette
		{
		public:
			//constructors
			Palette(void);

			//destructor
			~Palette(void);

			//color
			Color color(float, float, float) const;

			//name
			const char* name(void) const;
			static const char* name(palettes::type);

			//data
			uint32_t size(void) const;
			palettes::type type(void) const;
			palettes::type type(palettes::type);

		private:
			//load
			void load(palettes::type);

			//data
			uint32_t m_size;
			const float* m_colors;
			palettes::type m_type;
			static const float m_palette_jet[];
			static const float m_palette_greys[];
			static const float m_palette_plasma[];
			static const float m_palette_whylrd[];
			static const float m_palette_viridis[];
			static const float m_palette_moreland[];
			static const float m_palette_spectral[];
		};
	}
}