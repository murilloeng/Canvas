#pragma once

//std
#include <string>
#include <vector>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Anchor.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

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

			//buffers
			void vbo_size(uint32_t[]) const override;
			void ibo_size(uint32_t[]) const override;

			//draw
			void ibo_fill_data(uint32_t**) const;
			void vbo_fill_data(vertices::Vertex**) const;

			void setup(uint32_t[], uint32_t[]) override;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			float m_size;
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