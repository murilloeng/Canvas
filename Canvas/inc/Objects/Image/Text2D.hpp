#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"

#include "Canvas/Canvas/inc/Objects/Geometry.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"

namespace canvas
{
	namespace objects
	{
		class Text2D : public Geometry
		{
		public:
			//constructors
			Text2D(void);

			//destructor
			~Text2D(void);

			//data
			float size(float);
			float size(void) const;

			float angle(float);
			float angle(void) const;

			uint32_t font(uint32_t);
			uint32_t font(void) const;

			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			vec2 position(void) const;
			vec2 position(const vec2&);

			std::string string(void) const;
			std::string string(std::string);

			float line_spacing(float);
			float line_spacing(void) const;

		protected:
			//text
			uint32_t width(void) const;
			uint32_t height(void) const;
			uint32_t length(void) const;

			//setup
			void setup(void) override;

			//data
			void vbo_fill_data(void) const;
			void ibo_fill_data(void) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			float m_size;
			float m_angle;
			uint32_t m_font;
			Anchor m_anchor;
			vec2 m_position;
			std::string m_string;
			float m_line_spacing;
			std::vector<uint32_t> m_lines;
		};
	}
}