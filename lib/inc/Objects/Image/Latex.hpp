#pragma once

//canvas
#include "Canvas/lib/inc/Math/vec3.hpp"
#include "Canvas/lib/inc/Objects/Anchor.hpp"
#include "Canvas/lib/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Latex : public Geometry
		{
		public:
			//constructors
			Latex(void);

			//destructor
			~Latex(void);

			//data
			float size(float);
			float size(void) const;

			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			vec3 position(void) const;
			vec3 position(const vec3&);

			unsigned index(unsigned);
			unsigned index(void) const;

			vec3 direction(unsigned) const;
			vec3 direction(unsigned, const vec3&);

		protected:
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
			Anchor m_anchor;
			vec3 m_position;
			unsigned m_index;
			vec3 m_directions[2];
		};
	}
}