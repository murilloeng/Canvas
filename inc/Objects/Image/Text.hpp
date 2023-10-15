#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Anchor.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Text : public Object
		{
		public:
			//constructors
			Text(void);

			//destructor
			~Text(void);

			//data
			unsigned font(unsigned);
			unsigned font(void) const;

			unsigned size(unsigned);
			unsigned size(void) const;

			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			vec3 position(void) const;
			vec3 position(const vec3&);

			std::string text(void) const;
			std::string text(std::string);

			vec3 direction(unsigned) const;
			vec3 direction(unsigned, const vec3&);

		private:
			//text
			unsigned width(void) const;
			unsigned height(void) const;

			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;

			void setup(unsigned[], unsigned[]) override;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			unsigned m_font;
			unsigned m_size;
			Anchor m_anchor;
			vec3 m_position;
			std::string m_text;
			vec3 m_directions[2];
		};
	}
}