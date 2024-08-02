#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

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
			std::vector<vec2>& vertices(void);
			const std::vector<vec2>& vertices(void) const;

			std::vector<uint32_t>& loops(void);
			const std::vector<uint32_t>& loops(void) const;

		protected:
			//buffers
			void vbo_size(uint32_t[]) const override;
			void ibo_size(uint32_t[]) const override;

			//draw
			void ibo_fill_data(uint32_t**) const;
			void ibo_stroke_data(uint32_t**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			std::vector<vec2> m_vertices;
			std::vector<uint32_t> m_loops;
		};
	}
}