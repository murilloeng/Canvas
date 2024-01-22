#pragma once

//std
#include <string>
#include <vector>

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Anchor.hpp"
#include "inc/Objects/Geometry.hpp"

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

			unsigned font(unsigned);
			unsigned font(void) const;

			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			vec3 position(void) const;
			vec3 position(const vec3&);

			std::string text(void) const;
			std::string text(std::string);

			float line_spacing(float);
			float line_spacing(void) const;

			vec3 direction(unsigned) const;
			vec3 direction(unsigned, const vec3&);

		protected:
			//text
			unsigned width(void) const;
			unsigned height(void) const;
			unsigned length(void) const;

			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;

			void setup(unsigned[], unsigned[]) override;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			float m_size;
			unsigned m_font;
			Anchor m_anchor;
			vec3 m_position;
			std::string m_text;
			vec3 m_directions[2];
			float m_line_spacing;
			std::vector<unsigned> m_lines;
		};
	}
}