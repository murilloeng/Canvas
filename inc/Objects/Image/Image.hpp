#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Anchor.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Image : public Object
		{
		public:
			//constructors
			Image(void);

			//destructor
			~Image(void);

			//data
			float size(float);
			float size(void) const;

			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			vec3 position(void) const;
			vec3 position(const vec3&);

			unsigned image(unsigned);
			unsigned image(void) const;

			vec3 direction(unsigned) const;
			vec3 direction(unsigned, const vec3&);

		private:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			float m_size;
			Anchor m_anchor;
			vec3 m_position;
			unsigned m_image;
			vec3 m_directions[2];
		};
	}
}