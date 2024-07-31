#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"
#include "Canvas/inc/Objects/Tessellator.hpp"

namespace canvas
{
	namespace objects
	{
		class Polygon : public Geometry
		{
		public:
			//constructors
			Polygon(void);

			//destructor
			~Polygon(void);

			//data
			std::vector<vec2>& points(void);
			const std::vector<vec2>& points(void) const;

			std::vector<unsigned>& loops(void);
			const std::vector<unsigned>& loops(void) const;

		protected:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;

			void setup(unsigned[], unsigned[]) override;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			Tessellator m_tessellator;
		};
	}
}