#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	namespace palettes
	{
		class Palette
		{
		public:
			//types
			enum class Type : uint32_t
			{
				Jet,
				Greys,
				Plasma,
				Whylrd,
				Viridis,
				Moreland,
				Spectral,
				last
			};

			//constructors
			Palette(void);
			Palette(Type);

			//destructor
			~Palette(void);

			//color
			Color color(float, float, float) const;

			//name
			const char* name(void) const;
			static const char* name(Type);

			//data
			Type type(Type);
			Type type(void) const;
			uint32_t size(void) const;

		private:
			//load
			void load(Type);

			//data
			Type m_type;
			uint32_t m_size;
			const float* m_colors;
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