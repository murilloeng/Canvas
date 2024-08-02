#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Anchor.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Image : public Geometry
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

			uint32_t index(uint32_t);
			uint32_t index(void) const;

			vec3 direction(uint32_t) const;
			vec3 direction(uint32_t, const vec3&);

		protected:
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
			Anchor m_anchor;
			vec3 m_position;
			uint32_t m_index;
			vec3 m_directions[2];
		};
	}
}