#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"

#include "Canvas/Canvas/inc/Objects/Geometry.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"

namespace canvas
{
	namespace objects
	{
		class Text : public Geometry
		{
		public:
			//constructors
			Text(void);

			//destructor
			~Text(void);

			//data
			float size(float);
			float size(void) const;

			bool normal(bool);
			bool normal(void) const;

			uint32_t font(uint32_t);
			uint32_t font(void) const;

			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			vec3 position(void) const;
			vec3 position(const vec3&);

			std::string text(void) const;
			std::string text(std::string);

			float line_spacing(float);
			float line_spacing(void) const;

			vec3 direction(uint32_t) const;
			vec3 direction(uint32_t, const vec3&);

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

			//update
			void update_on_motion(void) const override;

			//data
			float m_size;
			bool m_normal;
			uint32_t m_font;
			Anchor m_anchor;
			vec3 m_position;
			std::string m_text;
			vec3 m_directions[2];
			float m_line_spacing;
			std::vector<uint32_t> m_lines;
		};
	}
}