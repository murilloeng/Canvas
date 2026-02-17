//std
#include <cstring>

//canvas
#include "Canvas/Canvas/inc/Fonts/Font.hpp"
#include "Canvas/Canvas/inc/Fonts/Glyph.hpp"

namespace canvas
{
	namespace fonts
	{
		//constructores
		Glyph::Glyph(void) : m_data(nullptr)
		{
			return;
		}

		//destructor
		Glyph::~Glyph(void)
		{
			delete[] m_data;
		}

		//data
		int64_t Glyph::width(void) const
		{
			return m_width;
		}
		int64_t Glyph::height(void) const
		{
			return m_height;
		}
		int64_t Glyph::offset(void) const
		{
			return m_offset;
		}
		int64_t Glyph::advance(void) const
		{
			return m_advance;
		}
		int64_t Glyph::bearing(uint32_t index) const
		{
			return m_bearings[index];
		}

		const uint8_t* Glyph::data(void) const
		{
			return m_data;
		}
		const Outline& Glyph::outline(void) const
		{
			return m_outline;
		}

		//draw
		void Glyph::coordinates(const Font* font, float* coordinates) const
		{
			//data
			const uint32_t w = font->texture().width();
			const uint32_t h = font->texture().height();
			//coordinates
			coordinates[2 * 2 + 1] = coordinates[2 * 3 + 1] = 0;
			coordinates[2 * 0 + 0] = coordinates[2 * 3 + 0] = float(m_offset) / w;
			coordinates[2 * 0 + 1] = coordinates[2 * 1 + 1] = float(m_height) / h;
			coordinates[2 * 1 + 0] = coordinates[2 * 2 + 0] = float(m_offset + m_width) / w;
		}

		//setup
		void Glyph::setup(FT_Face face, char code)
		{
			//metrics
			m_code = code;
			m_width = face->glyph->metrics.width >> 6;
			m_height = face->glyph->metrics.height >> 6;
			m_advance = face->glyph->metrics.horiAdvance >> 6;
			m_bearings[0] = face->glyph->metrics.horiBearingX >> 6;
			m_bearings[1] = face->glyph->metrics.horiBearingY >> 6;
			//outline
			m_outline.setup(face);
			//buffer
			if(m_data) delete[] m_data;
			m_data = new uint8_t[m_width * m_height];
			memcpy(m_data, face->glyph->bitmap.buffer, m_width * m_height * sizeof(uint8_t));
		}
	}
}