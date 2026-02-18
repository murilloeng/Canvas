#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Objects/Object.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"

namespace canvas
{
	namespace objects
	{
		class Text2D : public Object
		{
		public:
			//constructors
			Text2D(void);

			//destructor
			~Text2D(void);

			//data
			uint32_t font(uint32_t);
			uint32_t font(void) const;

			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			std::string text(void) const;
			std::string text(std::string);

		protected:
			//text
			uint32_t width(void) const;
			uint32_t height(void) const;
			uint32_t length(void) const;

			//data
			void vbo_fill_data(void) const;
			void ibo_fill_data(void) const;

			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			uint32_t m_font;
			Anchor m_anchor;
			std::string m_text;
		};
	}
}