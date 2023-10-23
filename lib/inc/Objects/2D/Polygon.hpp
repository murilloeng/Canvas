#pragma once

//std
#include <vector>

//canvas
#include "inc/Math/vec2.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Polygon : public Object
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

			//topology
			bool angle(unsigned, unsigned, unsigned) const;
			bool inside(unsigned, unsigned, unsigned, unsigned) const;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;

			void setup_link(void);
			void setup_list(void);
			void setup_triangles(void);
			void setup(unsigned[], unsigned[]) override;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			std::vector<vec2> m_points;
			std::vector<unsigned> m_list;
			std::vector<unsigned> m_loops;
			std::vector<unsigned> m_links[2];
			std::vector<unsigned> m_triangles;
		};
	}
}